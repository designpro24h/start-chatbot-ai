#pragma once
#include "AudioDevice.h"
#include "driver/i2s.h"

class MicINMP441 : public AudioDevice {
public:
  void begin();
  size_t read(int16_t* buffer, size_t len);
};
