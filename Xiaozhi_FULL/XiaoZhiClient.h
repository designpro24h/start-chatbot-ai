#pragma once
#include <WebSocketsClient.h>
#include "SpeakerI2S.h"


class XiaozhiClient {
public:
  static void init();
  static void loop();
  static void sendAudio(int16_t* pcm, size_t len);
};
