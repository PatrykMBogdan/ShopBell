#include "EspNowManager.h"

EspNowManager *EspNowManager::instance = nullptr;

void EspNowManager::init(){
    instance = this;
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Błąd inicjalizacji ESP-NOW");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
}

void EspNowManager::OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    if(instance == NULL) return;
    memcpy(&(instance->myMessage), incomingData, sizeof(myMessage));
    instance->isNewMessage = true;
}

bool EspNowManager::GetIsMessage(){
    if(isNewMessage){
        isNewMessage = false;
        return true;
    }
    else return false;
}

message EspNowManager::getLastMessage(){
    return myMessage;
}

transmiterStatus EspNowManager::getLastStatus(){
    return myMessage.status;
}

uint8_t EspNowManager::getBatteryPercent(){
    return myMessage.batteryPercent;
}