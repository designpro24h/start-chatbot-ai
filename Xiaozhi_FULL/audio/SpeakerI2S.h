#pragma once
#include "AudioDevice.h"
#include "driver/i2s.h"

class SpeakerI2S : public AudioDevice {
public:
  void begin();
  void play(uint8_t* data, size_t len);
};
