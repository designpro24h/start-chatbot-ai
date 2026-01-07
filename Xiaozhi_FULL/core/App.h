#pragma once

#include "AppState.h"
#include "../display/TFT_ST7735.h"
#include "../audio/Mic_INMP441.h"
#include "../audio/Speaker_I2S.h"
#include "../audio/VAD.h"
#include "../ai/XiaozhiAI.h"
#include "../input/Button.h"
#include "../config/Config.h"

class App {
public:
  void begin();
  void loop();

private:
  AppState state = AppState::IDLE;

  TFT_ST7735 display;
  Mic_INMP441 mic;
  Speaker_I2S speaker;
  XiaozhiAI ai;
  VAD vad;

  Button btnWake = Button(PIN_WAKE);
};
