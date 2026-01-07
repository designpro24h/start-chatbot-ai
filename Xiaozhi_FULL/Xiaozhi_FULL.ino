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
}

void loop() {
  XiaozhiClient::loop();

  if (ButtonManager::wakePressed()) {
    static int16_t micBuf[AUDIO_BUF];
    size_t len = MicINMP441::read(micBuf, AUDIO_BUF);
    XiaozhiClient::sendAudio(micBuf, len);
  }
}
