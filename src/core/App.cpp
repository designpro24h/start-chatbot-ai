#include "App.h"

void App::begin() {
  mic.begin();
  speaker.begin();
  btnWake.begin();
  ai.begin(&speaker);
}

void App::loop() {
  ai.loop();

  static int16_t buffer[AUDIO_BUF];

  if (btnWake.pressed()) {
    size_t len = mic.read(buffer, sizeof(buffer));
    ai.sendAudio((uint8_t*)buffer, len);
  }
}
