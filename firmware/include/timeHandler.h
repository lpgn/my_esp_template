#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

#include "config.h"

void printCompilationTimestamp();
void printRtcDateTime(const RtcDateTime &dt);
void syncInternalRtcWithExternal(const RtcDateTime &dt);
void initializeRtc();
void printRtcDateTimeInLoop();

#endif // WIFIHANDLER_H