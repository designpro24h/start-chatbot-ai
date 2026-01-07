#pragma once
#include "../audio/MicINMP441.h"
#include "../audio/SpeakerI2S.h"
#include "../input/Button.h"
#include "../ai/XiaoZhiClient.h"

class App {
public:
  void begin();
  void loop();

private:
  MicINMP441 mic;
  SpeakerI2S speaker;
  XiaoZhiClient ai;

  Button btnWake = Button(PIN_WAKE);
};
