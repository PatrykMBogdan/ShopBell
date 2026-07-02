#pragma once
#include <Arduino.h>

class BatteryManager{
    public:
        gpio_num_t batteryCheckPin;
        BatteryManager(gpio_num_t baterryCheckPin);
        float batteryLevel();
};