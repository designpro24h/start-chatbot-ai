#pragma once
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include "SpeakerI2S.h"


class XiaozhiClient {
public:
  static void init();
  static void loop();
  static void sendAudio(int16_t* pcm, size_t len);
  static void endAudio();          // ✅ đã dùng trong cpp

  //static void testSpeakHello();  

   // 🟢 trạng thái TTS
  static bool isSpeaking() { return speaking; }

   // 🔹 mới: lưu text mới từ Xiaozhi
    static String getText() { return lastText; }
    static void clearText() { lastText = ""; }



private:
  static WebSocketsClient ws;      // 🔥 KHAI BÁO ĐÚNG CHỖ
  static bool speaking;  // đang phát TTS

  static String lastText;           // 🔹 lưu text mới từ Xiaozhi

  static void onEvent(WStype_t type, uint8_t* payload, size_t length);
};