#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

constexpr gpio_num_t BATTERY_PIN = GPIO_NUM_34;
constexpr uint64_t MINUTES_TO_MICROSECONDS = 1000000*60;
constexpr uint64_t SLEEP_TIME = 0.15 * MINUTES_TO_MICROSECONDS;
constexpr uint8_t RECEIVER_MAC_ADDRESS[] = {0x1C, 0xC3, 0xAB, 0xC3, 0xD5, 0x30};
esp_now_peer_info_t peerInfo;

enum class transmiterStatus{
  standby,
  cooldown
};

struct message{
  transmiterStatus status;
  uint64_t sleepTime;
};

struct message myMessage;

void sendMessage(transmiterStatus status) {
  if(esp_now_init()!=ESP_OK){
    Serial.println("ERROR DURING INICIALIZATION OF ESPNOW");
    return;
  }
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, RECEIVER_MAC_ADDRESS, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("FAILED TO ADD RECEIVER");
        return;
  }
  myMessage.status = status;
  myMessage.sleepTime = SLEEP_TIME;
  esp_err_t result = esp_now_send(RECEIVER_MAC_ADDRESS, (uint8_t *) &myMessage, sizeof(myMessage));
  if (result == ESP_OK) {
        Serial.print("Wysłano pomyślnie. Status: ");
        Serial.println((int) status);
    }
    else {
        Serial.println("Błąd wysyłania");
    }
}

void Main(){
  esp_sleep_wakeup_cause_t wakeUpReason = esp_sleep_get_wakeup_cause();
  if(wakeUpReason == ESP_SLEEP_WAKEUP_TIMER){
    sendMessage(transmiterStatus::standby);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 1);
    delay(100);
    esp_deep_sleep_start();
  }
  else{
    sendMessage(transmiterStatus::cooldown);
    delay(100);
    esp_deep_sleep(SLEEP_TIME);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");
  WiFi.mode(WIFI_STA);
  Main();
}

void loop() {
}