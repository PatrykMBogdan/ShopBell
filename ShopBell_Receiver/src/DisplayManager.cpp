#include "DisplayManager.h"

Display::Display(){
}
void Display::init(){
    if(!display.begin(OLED_ADDRES,true)){
        Serial.println("Screen not found");
        while(true);
    }
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(1);
}
void Display::standbyMode(){
    display.clearDisplay();
}
void Display::showMenu(uint8_t cursorPosition, bool* doRedrawScreen){
    display.clearDisplay();
    display.setCursor(0,0);
    centerText("MENU"+String(cursorPosition),0);
    drawMenuOption("GLOSNOSC", 0, cursorPosition);
    drawMenuOption("GLOSNOSC", 1, cursorPosition);
    drawMenuOption("GLOSNOSC", 2, cursorPosition);
    redrawScreen(doRedrawScreen);
}

void Display::drawMenuOption(String optionName, uint8_t position, uint8_t cursorPosition){
    if(cursorPosition == position){
        drawSelectedMenuOption(optionName, position);
        return;
    }
    uint16_t y = position * (FONT_SIZE + LINE_SPACING) + TOP_SPACING;
    display.setCursor(LEFT_SPACING, y);
    display.print(optionName);
}

void Display::drawSelectedMenuOption(String optionName, uint8_t position){
    uint16_t y = position * (FONT_SIZE + LINE_SPACING) + TOP_SPACING;
    display.setCursor(LEFT_SPACING+LEFT_SPACING*0.2, y);
    display.print(optionName);
}

void Display::centerText(String text,uint16_t y){
    int16_t x1, y1;
    uint16_t textWidth, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &h);
    int x = display.width()/2 - textWidth/2;
    display.setCursor(x,y);
    display.println(text);
}
void Display::redrawScreen(bool* doRedrawScreen){
    display.display();
    *doRedrawScreen = false;
}