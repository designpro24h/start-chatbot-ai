#pragma once
#include <Adafruit_GFX.h>

class UIIcons {
public:
  static void drawMic(Adafruit_GFX* tft, int x, int y) {
    tft->fillRoundRect(x+6, y, 12, 20, 6, ST77XX_WHITE);
    tft->fillRect(x+10, y+20, 4, 6, ST77XX_WHITE);
    tft->drawLine(x+4, y+26, x+20, y+26, ST77XX_WHITE);
  }

  static void drawError(Adafruit_GFX* tft, int x, int y) {
    tft->drawLine(x, y, x+20, y+20, ST77XX_RED);
    tft->drawLine(x+20, y, x, y+20, ST77XX_RED);
  }
};
