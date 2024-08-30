#pragma once
#ifdef SENSORS
#include <ArduinoJson.h>

namespace HX711
{
    void Setup();
    void ConnectToWifi();
    void SerialReport();
    void Loop();
    bool SendDiscovery();
}

#endif
