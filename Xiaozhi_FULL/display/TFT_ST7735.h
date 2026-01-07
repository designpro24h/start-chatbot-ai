#pragma once
#include "DisplayBase.h"
#include "../core/AppState.h"   
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class TFT_ST7735 : public DisplayBase {
public:
  void begin() override;
  void showState(AppState state) override;

private:
  void drawCenterText(const char* text, uint16_t color);
};
