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

  static void testSpeak();  

private:
  static WebSocketsClient ws;      // 🔥 KHAI BÁO ĐÚNG CHỖ
};