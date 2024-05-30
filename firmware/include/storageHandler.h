/**
 * @file storageHandler.h
 * @brief Interface for storage management.
 *
 * Declares the StorageHandler class for managing data storage operations such as saving configurations,
 * reading logs, and handling file operations on the ESP filesystem.
 */

#ifndef STORAGE_HANDLER_H
#define STORAGE_HANDLER_H

#include "config.h"

bool writeFile(String path, String data);
String readFile(String path);
void setupStorage();
bool writeDataJson();
void readDataJson();
bool readAndParseJson(String& data, JsonDocument& doc);


#endif