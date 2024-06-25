#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

#include "config.h"

void formatDateTime(const RtcDateTime &dt, char* buffer, size_t size);
void syncInternalRtcWithExternal(const RtcDateTime &dt);
void initializeRtc();
void printCompileTime();
bool getCurrentTime(char *currentTime, size_t size);

#endif // WIFIHANDLER_H