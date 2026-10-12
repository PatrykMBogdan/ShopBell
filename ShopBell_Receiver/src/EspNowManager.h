#pragma once
#include <WiFi.h>
#include <esp_now.h>
#include "enum.h"

struct message{
  transmiterStatus status;
  uint64_t sleepTime;
};

class EspNowManager{
    private:
        static EspNowManager* instance;
        message myMessage;
        bool isNewMessage;
    public:
        void init();
        void static OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
        bool GetIsMessage();
        message getLastMessage();
        transmiterStatus getLastStatus();
};