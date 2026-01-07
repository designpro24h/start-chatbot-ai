#pragma once
#include <Arduino.h>

String base64Encode(uint8_t* data, size_t len);
uint8_t* base64Decode(const char* input, size_t len, size_t* outLen);
