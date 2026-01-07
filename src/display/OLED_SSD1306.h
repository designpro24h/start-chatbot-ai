#pragma once
#include "DisplayBase.h"

class OLED_SSD1306 : public DisplayBase {
public:
  void begin();
  void showStatus(const char* msg);
};
