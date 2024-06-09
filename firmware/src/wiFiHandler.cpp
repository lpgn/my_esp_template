#include "wiFiHandler.h"
#include "communication.h"

void printAccessPointIP()
{
    printAsciiBox("SoftAP IP is: " + WiFi.softAPIP().toString());
}

void printConnectedWiFiStatus()
{
    printAsciiBox("WiFi connected\nIP address: " + WiFi.localIP().toString());
}

void printDisconnectedWiFiStatus()
{
    printAsciiBox("WiFi not connected!");
}

void printWiFiScanStatus(int networkCount)
{
    if (networkCount == 0)
    {
        printAsciiBox("No WiFi networks found.");
    }
    else
    {
        printAsciiBox("Found " + String(networkCount) + " WiFi networks:");
    }
}

void printDiscoveredWiFiNetworks(int networkCount)
{
    for (int i = 0; i < networkCount; i++)
    {
        String message = String(i + 1) + ": " + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + " dBm";
        if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
        {
            message += ", open";
        }
        else
        {
            message += ", encrypted";
        }
        message += ")";
        printAsciiBox(message);
    }
}

void initiateWiFiConnection()
{
    printAsciiBox("Connecting Wifi...");
    if (wifiMulti.run() == WL_CONNECTED)
    {
        printConnectedWiFiStatus();
    }
    else
    {
        printAsciiBox("WiFi connection failed.");
    }
    WiFi.setTxPower(WIFI_POWER_19_5dBm);
}

void handleWiFiConnection()
{
    static unsigned long previousTime = 0;
    const unsigned long eventInterval = 10000;
    const uint32_t connectTimeoutMs = 10000;

    unsigned long currentTime = millis();

    if (currentTime - previousTime >= eventInterval)
    {
        if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED)
        {
            printAsciiBox("WiFi connected: " + WiFi.SSID());
        }
        else
        {
            printAsciiBox("WiFi connection failed.");
        }
        previousTime = currentTime;
    }
}

void scanAvailableWiFiNetworks()
{
    printAsciiBox("Scanning for WiFi networks...");
    int networkCount = WiFi.scanNetworks();
    printWiFiScanStatus(networkCount);
    printDiscoveredWiFiNetworks(networkCount);
}

void loadCredentialsFromFile()
{
    printAsciiBox("Reading credentials file...");
    String credentialsData = readFile("/credentials.txt");
    for (int pos = 0, foundAt = 0; foundAt != -1; pos = foundAt + 1)
    {
        foundAt = credentialsData.indexOf('\n', pos);
        String line = credentialsData.substring(pos, foundAt != -1 ? foundAt : credentialsData.length());
        int separatorIndex = line.indexOf(",");
        if (separatorIndex != -1)
        {
            String ssid = line.substring(0, separatorIndex);
            String password = line.substring(separatorIndex + 1);
            wifiMulti.addAP(ssid.c_str(), password.c_str());
            printAsciiBox("Loaded credential - SSID: " + ssid + ", Password: " + password);
        }
    }
}

void configureWiFiSettings()
{
    WiFi.mode(WIFI_MODE_APSTA);
    loadCredentialsFromFile();
    scanAvailableWiFiNetworks();
    initiateWiFiConnection();
}

void initializeServer()
{
    ElegantOTA.begin(&server);
    server.begin();
}
