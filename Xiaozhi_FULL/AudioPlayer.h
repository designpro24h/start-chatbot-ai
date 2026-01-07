#pragma once
#include <Arduino.h>

class AudioPlayer {
public:
  static void init();
  static void playPCM(int16_t* data, size_t samples);
};
