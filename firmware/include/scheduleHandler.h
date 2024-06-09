#ifndef SCHEDULE_HANDLER_H
#define SCHEDULE_HANDLER_H

#include "config.h"

bool isItTime(const char* currentTime, const char* times[], size_t numTimes);
void processModule(const char* currentTime, const JsonObject& module, const char* moduleName);
void checkFeedingSchedule();



#endif // SCHEDULE_HANDLER_H