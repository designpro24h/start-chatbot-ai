#include "DisplayManager.h"
#include "Config.h"

#include <SPI.h>

static Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

void DisplayManager::init() {
  SPI.begin(TFT_SCK, -1, TFT_MOSI);

  // tft.initR(INITR_BLACKTAB);
  // tft.fillScreen(ST77XX_BLACK);
  // tft.setRotation(1);
  // tft.setTextColor(ST77XX_WHITE);
  // tft.setTextSize(2);
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.println("Init LCD...");
}


void DisplayManager::showText(const String& txt) {
  // tft.fillScreen(ST77XX_BLACK);
  // tft.setCursor(0, 20);
  // tft.print(txt);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.println(txt);
    Serial.print("[LCD] "); Serial.println(txt);
}

void DisplayManager::drawWaveColumn(int col, int height) {
    tft.fillRect(col*2, 30, 2, 60, ST77XX_BLACK);  // clear cột cũ
    tft.fillRect(col*2, 90-height, 2, height, ST77XX_GREEN);
}