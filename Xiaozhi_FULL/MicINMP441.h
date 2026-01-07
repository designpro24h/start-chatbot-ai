#pragma once
#include <Arduino.h>

class MicINMP441 {
public:
  static void init();
  static size_t read(int16_t* buffer, size_t len);
};
