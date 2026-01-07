#pragma once
#include <WebSocketsClient.h>
#include "../audio/SpeakerI2S.h"

class XiaoZhiClient {
  WebSocketsClient ws;
  SpeakerI2S* speaker;
public:
  void begin(SpeakerI2S* spk);
  void loop();
  void sendAudio(uint8_t* data, size_t len);
};
