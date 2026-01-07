#include "Base64.h"
#include "mbedtls/base64.h"

String base64Encode(uint8_t* data, size_t len) {
  size_t outLen;
  uint8_t out[4 * ((len + 2) / 3)];

  mbedtls_base64_encode(out, sizeof(out), &outLen, data, len);
  return String((char*)out);
}

uint8_t* base64Decode(const char* input, size_t len, size_t* outLen) {
  uint8_t* out = (uint8_t*)malloc(len);
  mbedtls_base64_decode(out, len, outLen, (uint8_t*)input, len);
  return out;
}
