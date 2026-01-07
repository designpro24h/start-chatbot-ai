#include "Config.h"
#include "WiFiManager.h"
#include "ButtonManager.h"
#include "MicINMP441.h"
#include "DisplayManager.h" 
#include "AudioPlayer.h"

#include "MicINMP441.h"

#include "XiaozhiClient.h"

int16_t micBuf[AUDIO_BUF];

void setup() {
  Serial.begin(115200);
  delay(500);

  // ===== LCD =====
  DisplayManager::init();
  DisplayManager::showText("BOOTING...");

  // ===== WIFI =====
  WiFiManager::connect();
  DisplayManager::showText("WIFI OK");

  // ===== INPUT =====
  ButtonManager::init();

  // ===== AUDIO =====
  MicINMP441::init();
  AudioPlayer::init();

  // ===== XIAOZHI =====
  XiaozhiClient::init();
  DisplayManager::showText("XIAOZHI READY");

  Serial.println("Xiaozhi AI Ready");

  delay(2000);              // ⏳ chờ websocket ổn định
  XiaozhiClient::testSpeak(); // 🔥 TEST NÓI
}

// void loop() {
//   XiaozhiClient::loop();

//   if (ButtonManager::wakePressed()) {
//     static int16_t micBuf[AUDIO_BUF];
//     size_t len = MicINMP441::read(micBuf, AUDIO_BUF);
//     XiaozhiClient::sendAudio(micBuf, len);
//   }
// }
static unsigned long lastSend = 0;
static bool talking = false;

void loop() {
  XiaozhiClient::loop();

  if (ButtonManager::wakePressed()) {
    talking = true;

    if (millis() - lastSend > 40) {   // ~25 gói / giây
      static int16_t micBuf[AUDIO_BUF];
      size_t len = MicINMP441::read(micBuf, AUDIO_BUF);
      XiaozhiClient::sendAudio(micBuf, len);
      lastSend = millis();

      DisplayManager::showText("LISTENING...");
    }
  }
  else if (talking) {
    // vừa nhả nút xong → kết thúc nói
    XiaozhiClient::endAudio();
    DisplayManager::showText("PROCESSING...");
    talking = false;
  }
}