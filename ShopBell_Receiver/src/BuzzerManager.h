#pragma once
#include <Arduino.h>

class BuzzerManager{
    private:
    gpio_num_t BuzzerPin;
    uint64_t soundStart = 0;
    uint64_t PlayingTime = 1 * 1000;
    uint16_t soundFrequency;
    bool isActive;
    void playSound();
    void stopSound();
    uint64_t soundTimer();
    public: 
    BuzzerManager(gpio_num_t BuzzerPin, uint16_t soundFrequency);
    void useBuzzer();
    void init();
    void process();
};