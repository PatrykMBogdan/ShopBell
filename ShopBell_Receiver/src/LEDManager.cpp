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
    gpio_set_level(ledRed, HIGH);
}

void LedManager::ledGreenOn(){
    gpio_set_level(ledGreen, HIGH);
}

void LedManager::ledAllOn(){
    gpio_set_level(ledGreen, HIGH);
    gpio_set_level(ledRed, HIGH);
}

void LedManager::ledRedOff(){
    gpio_set_level(ledRed, LOW);
}

void LedManager::ledGreenOff(){
    gpio_set_level(ledGreen, LOW);
}

void LedManager::ledAllOff(){
    gpio_set_level(ledGreen, LOW);
    gpio_set_level(ledRed, LOW);
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