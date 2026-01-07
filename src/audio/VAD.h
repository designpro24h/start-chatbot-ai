#pragma once
#include <stdint.h>
#include <stddef.h>

class VAD {
public:
  VAD(int threshold, int silenceMs);

  bool isSpeech(int16_t* samples, size_t count);
  bool shouldStop();

private:
  int threshold;
  int silenceTimeout;
  unsigned long lastSpeechTime;
};
