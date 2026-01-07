#pragma once
#include <Arduino.h>

class SpeakerI2S {
public:
  void begin();
  void play(const int16_t* data, size_t len);
};
