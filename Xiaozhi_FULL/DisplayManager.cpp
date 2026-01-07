#include "DisplayManager.h"
#include "Config.h"

#include <SPI.h>

static Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

void DisplayManager::init() {
  SPI.begin(TFT_SCK, -1, TFT_MOSI);

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
}

void DisplayManager::showText(const char* txt) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 20);
  tft.print(txt);
}