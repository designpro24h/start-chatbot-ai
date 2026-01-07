#include "MicINMP441.h"
#include "../core/Config.h"

void MicINMP441::begin() {
  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .dma_buf_count = 6,
    .dma_buf_len = AUDIO_BUF
  };

  i2s_pin_config_t pin = {
    .bck_io_num = MIC_SCK,
    .ws_io_num  = MIC_WS,
    .data_out_num = -1,
    .data_in_num  = MIC_SD
  };

  i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin);
}

size_t MicINMP441::read(int16_t* buffer, size_t len) {
  size_t bytes;
  i2s_read(I2S_NUM_0, buffer, len, &bytes, portMAX_DELAY);
  return bytes;
}
