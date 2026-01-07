#include "Config.h"
#include "SpeakerI2S.h"
#include "pins.h"
#include <driver/i2s.h>

void SpeakerI2S::begin() {
  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 4,
    .dma_buf_len = 256,
    .use_apll = false
  };

  i2s_pin_config_t pin = {
    .bck_io_num = SPK_BCK,
    .ws_io_num  = SPK_WS,
    .data_out_num = SPK_DOUT,
    .data_in_num = -1
  };

  i2s_driver_install(I2S_NUM_1, &cfg, 0, NULL);
  i2s_set_pin(I2S_NUM_1, &pin);
}

void SpeakerI2S::play(const int16_t* data, size_t len) {
  size_t bytes;
  i2s_write(I2S_NUM_1, data, len * 2, &bytes, portMAX_DELAY);
}
