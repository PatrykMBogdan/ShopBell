#include <Arduino.h>
#include "LedManager.h"
#include "EspNowManager.h"
#include "BuzzerManager.h"


constexpr uint32_t MILLIS_TO_SECONDS = 1000000;
constexpr gpio_num_t LED_GREEN = GPIO_NUM_23;
constexpr gpio_num_t LED_RED = GPIO_NUM_25;
constexpr gpio_num_t BUZZER_PIN = GPIO_NUM_5;
uint8_t cursorPosition = 0;

LedManager Led(LED_RED, LED_GREEN);
EspNowManager ComunicationManager;
BuzzerManager Buzzer(BUZZER_PIN, 440);

void comunicationHandler();

void setup() {
  Serial.begin(115200);
  Serial.println("Booting up...");
  ComunicationManager.init();
  Led.init();
  Buzzer.init();
  Serial.println("Booting succsefull");
}

void loop() {
  comunicationHandler();
  Buzzer.process();
}

void comunicationHandler(){
  if(ComunicationManager.GetIsMessage()){
    Led.showStatus(ComunicationManager.getLastStatus());
    if(ComunicationManager.getLastStatus() == transmiterStatus::cooldown)
      Buzzer.useBuzzer();
    Serial.println("Message received");
  }
}
