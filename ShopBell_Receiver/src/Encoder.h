#pragma once
#include <Arduino.h>

constexpr uint32_t DEBOUNCING_TIME_BUTTON = 250;
constexpr uint32_t DEBOUNCING_TIME_ENCODER = 10;

class Encoder{
    private:
        uint8_t buttonPin, s1Pin, s2Pin;
        volatile uint8_t lastState;
        volatile int8_t internalCounter = 0;
        volatile uint32_t lastClick = millis(), lastRotation = millis();
        static Encoder* instance;
        void handleInterruptRotation();
        void handleInterruptButton();
    public:
        Encoder(uint8_t buttonPin, uint8_t s1Pin, uint8_t s2Pin);
        volatile bool hasButtonBeenPressed = false, hasRotatedLeft = false, hasRotatedRight = false;
        static void IRAM_ATTR isrS1();
        static void IRAM_ATTR isrButton();
        void init();
        void read(uint8_t* cursorPosition, bool* isButtonPressed, bool* doRedrawScreen);
        void rotateLeft(uint8_t* cursorPosition);
        void rotateRight(uint8_t* cursorPosition);
        void buttonPressed(bool* isButtonPressed);
};