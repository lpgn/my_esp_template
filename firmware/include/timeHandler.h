#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

#include "config.h"
void formatDateTime(const RtcDateTime &dt, char* buffer, size_t size);
void printRtcDateTime(const RtcDateTime &dt);
void syncInternalRtcWithExternal(const RtcDateTime &dt);
void initializeRtc();
bool getCurrentTime(char* currentTime, size_t currentTimeSize);

#endif // WIFIHANDLER_H