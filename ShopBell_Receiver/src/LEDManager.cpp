#include "LEDManager.h"

LedManager::LedManager(gpio_num_t ledRed, gpio_num_t ledGreen){
    this->ledRed = ledRed;
    this->ledGreen = ledGreen;
}

void LedManager::init(){
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    delay(100);
    ledAllOff();
}

void LedManager::ledRedOn(){
    digitalWrite(ledRed, HIGH);
}

void LedManager::ledGreenOn(){
    digitalWrite(ledGreen, HIGH);
}

void LedManager::ledAllOn(){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, HIGH);
}

void LedManager::ledRedOff(){
    digitalWrite(ledRed, LOW);
}

void LedManager::ledGreenOff(){
    digitalWrite(ledGreen, LOW);
}

void LedManager::ledAllOff(){
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, LOW);
}

void LedManager::ledStatusCooldown(){
    ledGreenOff();
    ledRedOn();
}

void LedManager::ledStatusStandby(){
    ledRedOff();
    ledGreenOn();
}

void LedManager::showStatus(transmiterStatus status){
  switch (status)
  {
  case transmiterStatus::cooldown:
    ledStatusCooldown();
    break;
  case transmiterStatus::standby:
    ledStatusStandby();
    break;
  default:
    break;
  }
}