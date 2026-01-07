#include "VAD.h"

VAD::VAD(int threshold, int silenceMs) {
  th = threshold;
  silence = silenceMs;
}

bool VAD::detect(const int16_t* buf, size_t len) {
  long sum = 0;
  for (size_t i = 0; i < len; i++) sum += abs(buf[i]);

  if (sum / len > th) {
    lastVoice = millis();
    return true;
  }
  return millis() - lastVoice < silence;
}

void VAD::reset() {
  lastVoice = 0;
}
