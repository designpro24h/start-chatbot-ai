#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class DisplayManager {
public:
  static void init();
  static void showText(const char* txt);
};
