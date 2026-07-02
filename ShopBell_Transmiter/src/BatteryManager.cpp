#include "BatteryManager.h"

BatteryManager::BatteryManager(gpio_num_t batteryCheckPin){
    this->batteryCheckPin = batteryCheckPin;
}

float BatteryManager::batteryLevel(){
    analogRead(this->batteryCheckPin);
    return 2.4;
}