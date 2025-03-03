/**
 * @file WiFiHandler.h
 * @brief Interface for WiFi connectivity.
 *
 * Declares the WiFiHandler class for managing WiFi connections. This includes methods
 * for connecting to networks, handling disconnections, and maintaining WiFi stability.
 */

#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include "config.h"

void printAccessPointIP();
void printConnectedWiFiStatus();
void printDisconnectedWiFiStatus();
void printWiFiScanStatus(int networkCount);
void printDiscoveredWiFiNetworks(int networkCount);
void initiateWiFiConnection();
void handleWiFiConnection();
void scanAvailableWiFiNetworks();
void configureWiFiSettings();
void loadCredentialsFromFile();
void initializeServer();
#endif // WIFIHANDLER_H