#include "SpeakerI2S.h"
#include "../core/Config.h"

void SpeakerI2S::begin() {
  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .dma_buf_count = 6,
    .dma_buf_len = AUDIO_BUF
  };

  i2s_driver_install(I2S_NUM_1, &cfg, 0, NULL);
}

void SpeakerI2S::play(uint8_t* data, size_t len) {
  size_t written;
  i2s_write(I2S_NUM_1, data, len, &written, portMAX_DELAY);
}
