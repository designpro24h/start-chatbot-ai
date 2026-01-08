#include <Arduino.h>
#include "Config.h"
#include "WiFiManager.h"
#include "ButtonManager.h"
#include "MicINMP441.h"
#include "DisplayManager.h" 
#include "AudioPlayer.h"
#include "MicINMP441.h"
#include "XiaozhiClient.h"



#define WAKE_WORD_PIN PIN_WAKE


bool wakeDetected = false;

void IRAM_ATTR onWakePress() {
    wakeDetected = true;  // detect wake word button press
}

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
  // 
  pinMode(WAKE_WORD_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WAKE_WORD_PIN), onWakePress, FALLING);


  // ===== AUDIO =====
  MicINMP441::init();
  AudioPlayer::init();

  // ===== XIAOZHI =====
  XiaozhiClient::init();
  DisplayManager::showText("XIAOZHI READY");

  Serial.println("Xiaozhi AI Ready");

  delay(2000);              // ⏳ chờ websocket ổn định
  //XiaozhiClient::testSpeakHello(); // 🔥 TEST NÓI
}


static unsigned long lastSend = 0;
static bool talking = false;

//void loop() {
  // XiaozhiClient::loop();

  // if (ButtonManager::wakePressed()) {
  //   talking = true;

  //   if (millis() - lastSend > 40) {   // ~25 gói / giây
  //     static int16_t micBuf[AUDIO_BUF];
  //     size_t len = MicINMP441::read(micBuf, AUDIO_BUF);
  //     XiaozhiClient::sendAudio(micBuf, len);
  //     lastSend = millis();

  //     DisplayManager::showText("LISTENING...");
  //   }
  // }
  // else if (talking) {
  //   // vừa nhả nút xong → kết thúc nói
  //   XiaozhiClient::endAudio();
  //   DisplayManager::showText("PROCESSING...");
  //   talking = false;
  // }
//}

void loop() {
   XiaozhiClient::loop();

    static const size_t RECORD_SAMPLES = SAMPLE_RATE * 2; // 2s buffer
    static int16_t* pcmBuffer = nullptr;
    if (!pcmBuffer) pcmBuffer = (int16_t*)malloc(RECORD_SAMPLES * sizeof(int16_t));

    if (wakeDetected) {
        wakeDetected = false;
        DisplayManager::showText("LISTENING...");
        Serial.println("[WAKE] Recording audio...");

        // 🔹 Ghi âm từ MIC
        MicINMP441::recordPCM(pcmBuffer, RECORD_SAMPLES);

        // 🔹 Gửi đến Xiaozhi
        XiaozhiClient::sendAudio(pcmBuffer, RECORD_SAMPLES);
        XiaozhiClient::endAudio();

        DisplayManager::showText("WAIT TTS...");
        Serial.println("[WAKE] Audio sent, waiting for TTS...");
    }

     // 🔹 hiển thị text trả lời Xiaozhi
    String txt = XiaozhiClient::getText();
    if (txt.length() > 0) {
        
        DisplayManager::showText(txt.c_str());
        XiaozhiClient::clearText();  // xóa sau khi hiển thị
    }

    // 🔹 Hiển thị waveform realtime
    if (!XiaozhiClient::isSpeaking()) {
        for (size_t i = 0; i < 80; i++) {
            int16_t sample = pcmBuffer[i * (RECORD_SAMPLES / 80)];
            int height = map(sample, -30000, 30000, 0, 60);
            DisplayManager::drawWaveColumn(i, height); // cần viết drawWaveColumn trong DisplayManager
        }
    }
}
