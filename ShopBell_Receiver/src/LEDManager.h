#pragma once
#include <Arduino.h>
#include "enum.h"

class LedManager{
    private:
        gpio_num_t ledRed;
        gpio_num_t ledGreen;
    public:
        LedManager(gpio_num_t ledRed, gpio_num_t ledGreen);
        void init();
        void ledRedOn();
        void ledGreenOn();
        void ledAllOn();
        void ledRedOff();
        void ledGreenOff();
        void ledAllOff();
        void ledStatusCooldown();
        void ledStatusStandby();
        void showStatus(transmiterStatus status);
};