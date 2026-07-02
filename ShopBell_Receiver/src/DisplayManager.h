#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr int8_t OLED_RESET_PIN = -1;
constexpr uint8_t OLED_ADDRES = 0x3c;
constexpr uint8_t FONT_SIZE = 7;
constexpr uint8_t LINE_SPACING = 4;
constexpr uint8_t LEFT_SPACING = 12;
constexpr uint8_t TOP_SPACING = FONT_SIZE + LINE_SPACING + 2;

class Display{
    private:
        Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);
    public:
        Display();
        void init();
        void standbyMode();
        void showMenu(uint8_t cursorPosition);
        void centerText(String text, uint16_t y);
        void drawMenuOption(String optionName, uint8_t position, uint8_t cursorPosition);
        void drawSelectedMenuOption(String optionName, uint8_t position);
};