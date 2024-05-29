#ifndef HANLE_TEMPLATE_TPP
#define HANLE_TEMPLATE_TPP

#include "config.h"

// Template function implementation
template <typename T>
void handleTemplate(AsyncWebServerRequest *request, const char* paramName, 
    void (*setterFunction)(T), const char* successMessage) {
    if (request->hasParam(paramName)) {
        T value = static_cast<T>(request->getParam(paramName)->value().toDouble());
        setterFunction(value);
        request->send(200, "text/plain", String(successMessage) + ": " + String(value));
    } else {
        request->send(400, "text/plain", String(paramName) + " parameter is missing");
    }
}

// Non-blocking delay function template
template<typename Callback>
void nonBlockingDelay(unsigned long interval, Callback callback, unsigned long &lastMillis) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastMillis >= interval) {
        lastMillis = currentMillis;
        callback();
    }
}

#endif
