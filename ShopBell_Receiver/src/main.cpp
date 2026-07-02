#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "Encoder.h"
#include "DisplayManager.h"

constexpr uint32_t MILLIS_TO_SECONDS = 1000000;
constexpr gpio_num_t LED_GREEN = GPIO_NUM_23;
constexpr gpio_num_t LED_RED = GPIO_NUM_25;
uint8_t cursorPosition = 0;
bool isButtonPressed = false;
bool doRedrawScreen = false;
Display oled;
Encoder EC11(4,18,19);

void controlsMenu();
void mainMenu();
void transmiterSettings();

enum class transmiterStatus{
  standby,
  cooldown
};

struct message{
  transmiterStatus status;
  uint64_t sleepTime;
  float batteryLevel;
};

struct message myMessage;

void resetAllLED(){
  gpio_set_level(LED_GREEN, LOW);
  gpio_set_level(LED_RED, LOW);
}

void LEDSetUp(){
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  delay(100);
  resetAllLED();
}

void transmiterStatusStandby(){
  resetAllLED();
  gpio_set_level(LED_GREEN, HIGH);
}

void transmiterStatusCooldown(){
  resetAllLED();
  gpio_set_level(LED_RED, HIGH);
}

void transmiterManager(transmiterStatus status){
  switch (status)
  {
  case transmiterStatus::cooldown:
    transmiterStatusCooldown();
    break;
  case transmiterStatus::standby:
    transmiterStatusStandby();
    break;
  default:
    break;
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&myMessage, incomingData, sizeof(myMessage));
    Serial.println("Odebrano wiadomosc"+String((int)myMessage.status));
    transmiterManager(myMessage.status);
}

enum class MachineStates{
  mainMenu,
  transmitterSettings,
  count
};


void setup() {
  LEDSetUp();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Błąd inicjalizacji ESP-NOW");
    return;
  }
  Serial.println(WiFi.macAddress());
  esp_now_register_recv_cb(OnDataRecv);
  EC11.init();
  oled.init();
  oled.showMenu(cursorPosition);
}

void loop() {
  mainMenu();
}

void mainMenu(){
  controlsMenu();
  if (doRedrawScreen){
      oled.showMenu(cursorPosition);
      doRedrawScreen = false;
  }
}

void controlsMenu(){
  if (EC11.hasRotatedRight) {
      cursorPosition = (cursorPosition + 1) % (int)MachineStates::count;
      doRedrawScreen = true;
      EC11.hasRotatedRight = false;
      Serial.println("Turned right");
  }
  else if (EC11.hasRotatedLeft) {
      cursorPosition = (cursorPosition + (int)MachineStates::count - 1) % (int)MachineStates::count; 
      doRedrawScreen = true;
      EC11.hasRotatedLeft = false;
      Serial.println("Turned Left");
  }
  if(EC11.hasButtonBeenPressed){
    EC11.hasButtonBeenPressed = false;
    isButtonPressed = true;
    doRedrawScreen = true;
    Serial.println("Button got clicked on menu postion: " + String(cursorPosition));
  }
}
void transmitterSettings(){
  
}