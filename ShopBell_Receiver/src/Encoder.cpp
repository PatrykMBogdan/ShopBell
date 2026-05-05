#include "Encoder.h"
constexpr uint8_t MENUS_COUNT = 3;

Encoder *Encoder::instance = nullptr;

Encoder::Encoder(uint8_t buttonPin, uint8_t s1Pin, uint8_t s2Pin){
    this->buttonPin = buttonPin;
    this->s1Pin = s1Pin;
    this->s2Pin = s2Pin;
}

void Encoder::init(){
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(s1Pin, INPUT_PULLUP);
    pinMode(s2Pin, INPUT_PULLUP);
    instance = this;
    lastClick = millis();
    lastState = digitalRead(s1Pin);
    attachInterrupt(digitalPinToInterrupt(s1Pin), isrS1, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonPin), isrButton, FALLING);
}
void IRAM_ATTR Encoder::isrS1(){
    if(instance!=nullptr) instance->handleInterruptRotation();
}

void Encoder::handleInterruptRotation(){
    if(millis()-lastRotation < DEBOUNCING_TIME_ENCODER) return;
    lastRotation = millis();
    if(lastState!=digitalRead(s1Pin)){
        lastState=digitalRead(s1Pin);
        if(lastState==digitalRead(s2Pin)){
            internalCounter++;
        }
        else{
            internalCounter--;
        }
    }
    if(internalCounter%2 == 0){
        if(internalCounter > 0) hasRotatedRight = true;
        else if(internalCounter < 0) hasRotatedLeft = true;
        internalCounter = 0;
    }
}

void IRAM_ATTR Encoder::isrButton(){
    if(instance!=nullptr) instance->handleInterruptButton();
}

void Encoder::handleInterruptButton(){
    if(millis()-lastClick > DEBOUNCING_TIME_BUTTON){
        lastClick = millis();
        hasButtonBeenPressed = true;
    }
}

void Encoder::buttonPressed(bool* isButtonPressed){
    Serial.println("Button got pressed!");
    *isButtonPressed = true;
    hasButtonBeenPressed = false;
}

void Encoder::rotateLeft(uint8_t* cursorPosition){
    Serial.println("Rotated Left!");
    *cursorPosition = (*cursorPosition + MENUS_COUNT - 1) % MENUS_COUNT;
    hasRotatedLeft = false;
}

void Encoder::rotateRight(uint8_t* cursorPosition){
    Serial.println("Rotated Right!");
    *cursorPosition = (*cursorPosition + 1) % MENUS_COUNT;
    hasRotatedRight = false;
}

void Encoder::read(uint8_t* cursorPosition, bool* isButtonPressed, bool* doRedrawScreen){
    if(hasButtonBeenPressed) buttonPressed(isButtonPressed);
    if(hasRotatedLeft) rotateLeft(cursorPosition);
    else if(hasRotatedRight) rotateRight(cursorPosition);
    if(hasButtonBeenPressed || hasRotatedRight || hasRotatedLeft) *doRedrawScreen = true;
}