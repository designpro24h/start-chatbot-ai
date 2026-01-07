#include "TFT_ST7735.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "../core/Config.h"

Adafruit_ST7735 tft = Adafruit_ST7735(
  TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST
);

void TFT_ST7735::begin() {
  SPI.begin(TFT_SCK, -1, TFT_MOSI);
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1); // landscape
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextSize(2);
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(10, 60);
  tft.println("Xiaozhi");
}

void TFT_ST7735::drawCenterText(const char* text, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(color);

  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int x = (160 - w) / 2;
  int y = (128 - h) / 2;

  tft.setCursor(x, y);
  tft.println(text);
}

void TFT_ST7735::showState(AppState state) {
  tft.fillScreen(ST77XX_BLACK);

  switch (state) {

    case AppState::IDLE:
      UIIcons::drawMic(&tft, 54, 40);
      break;

    case AppState::LISTENING:
      animator.drawWave(&tft, 64, 80);
      break;

    case AppState::THINKING:
      animator.drawThinking(&tft, 20, 70);
      break;

    case AppState::SPEAKING:
      animator.drawWave(&tft, 64, 80);
      tft.setCursor(30, 120);
      tft.setTextColor(ST77XX_WHITE);
      tft.print("Speaking");
      break;

    case AppState::ERROR:
      UIIcons::drawError(&tft, 54, 60);
      break;
  }
}
