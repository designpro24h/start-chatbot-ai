#include "VAD.h"
#include <Arduino.h>
#include <math.h>

VAD::VAD(int th, int silenceMs)
: threshold(th), silenceTimeout(silenceMs), lastSpeechTime(0) {}

bool VAD::isSpeech(int16_t* samples, size_t count) {
  long sum = 0;
  for (size_t i = 0; i < count; i++) {
    sum += abs(samples[i]);
  }

  int avg = sum / count;

  if (avg > threshold) {
    lastSpeechTime = millis();
    return true;
  }
  return false;
}

bool VAD::shouldStop() {
  return (millis() - lastSpeechTime) > silenceTimeout;
}
