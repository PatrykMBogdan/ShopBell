#include "BuzzerManager.h"

BuzzerManager::BuzzerManager(gpio_num_t BuzzerPin, uint16_t soundFrequency){
    this->BuzzerPin = BuzzerPin;
    this->soundFrequency = soundFrequency;
    this->isActive = 0;
}

void BuzzerManager::init(){
    ledcSetup(0, soundFrequency, 8);
    ledcAttachPin(BuzzerPin, 0);
    ledcWrite(0, 0);
}

void BuzzerManager::playSound(){
    ledcWrite(0, 127);
}

void BuzzerManager::stopSound(){
    ledcWrite(0, 0);
    Serial.println("Wylaczam buzzer...");
}

uint64_t BuzzerManager::soundTimer(){
    if(soundStart == 0) soundStart = millis();
    return millis() - soundStart;
}

void BuzzerManager::useBuzzer(){
    isActive = true;
    playSound();
}

void BuzzerManager::process(){
    if(isActive)
        if(soundTimer() > PlayingTime){
            isActive = false;
            stopSound();
            soundStart = 0;
        }
}