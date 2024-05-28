/**
 * @file storageHandler.cpp
 * @brief Implements storage management functions.
 *
 * Implements methods of the StorageHandler class. These methods manage all interactions with
 * the device's non-volatile storage, providing functionality to save and load configurations.
 */

#include "storageHandler.h"

bool writeFile(String path, String data)
{
    File file = LittleFS.open(path, "w");
    if (!file)
    {
        Serial.printf("Failed to open file '%s' for writing\n", path.c_str());
        return false;
    }
    int bytesWritten = file.print(data);
    file.close();
    Serial.printf("Written to file '%s' (%d bytes)\n", path.c_str(), bytesWritten);
    return true;
}

String readFile(String path)
{
    if (!LittleFS.exists(path))
    {
        Serial.printf("File '%s' does not exist\n", path.c_str());
        return "";
    }
    File file = LittleFS.open(path, "r");
    String data = file.readString();
    file.close();
    return data;
}

void setupStorage()
{
    if (!LittleFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
}

// // Function to read data from a file
// String readFile(String path)
// {
//     File file = LittleFS.open(path, "r");
//     if (!file)
//     {
//         Serial.printf("Failed to open file '%s' for reading\n", path.c_str());
//         return "";
//     }
//     String data = file.readString();
//     file.close();
//     Serial.printf("Read from file '%s'\n", path.c_str());
//     return data;
// }