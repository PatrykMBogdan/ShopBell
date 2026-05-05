#include <Arduino.h>
#include <WiFi.h>
#include "Encoder.h"
#include "DisplayManager.h"

uint8_t cursorPosition = 0;
bool isButtonPressed = false;
bool doRedrawScreen = true;
Display oled;
Encoder EC11(4,18,19);

void setup() {
  Serial.begin(115200);
  EC11.init();
  oled.init();
  oled.showMenu(cursorPosition, &doRedrawScreen);
}

void loop() {
  EC11.read(&cursorPosition, &isButtonPressed, &doRedrawScreen);
  oled.showMenu(cursorPosition, &doRedrawScreen);
}
