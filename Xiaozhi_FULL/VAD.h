#pragma once
#include <Arduino.h>

class VAD {
public:
  VAD(int threshold, int silenceMs);
  bool detect(const int16_t* buf, size_t len);
  void reset();

private:
  int th;
  unsigned long lastVoice = 0;
  int silence;
};
