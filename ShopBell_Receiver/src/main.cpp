#include <Arduino.h>
#include "LedManager.h"
#include "EspNowManager.h"

constexpr uint32_t MILLIS_TO_SECONDS = 1000000;
constexpr gpio_num_t LED_GREEN = GPIO_NUM_23;
constexpr gpio_num_t LED_RED = GPIO_NUM_25;
uint8_t cursorPosition = 0;

LedManager Led(LED_RED, LED_GREEN);
EspNowManager ComunicationManager;

void comunicationHandler();

void setup() {
  Serial.begin(115200);
  Serial.println("Booting up...");
  ComunicationManager.init();
  Led.init();
  Serial.println("Booting succsefull");
}

void loop() {
  comunicationHandler();
}

void comunicationHandler(){
  if(ComunicationManager.GetIsMessage()){
    Led.showStatus(ComunicationManager.getLastStatus());
    Serial.println("Message received");
  }
}
