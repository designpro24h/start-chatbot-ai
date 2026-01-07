#include "App.h"
#include "../audio/VAD.h"

void App::begin() {
  mic.begin();
  speaker.begin();
  btnWake.begin();
  ai.begin(&speaker);
}

void App::loop() {
  ai.loop();

  static int16_t buffer[AUDIO_BUF];
  size_t len = mic.read(buffer, sizeof(buffer));

  /* ===== WAKE BUTTON ===== */
  if (btnWake.pressed()) {
    listening = true;
  }

  /* ===== VAD LOGIC ===== */
  if (listening) {
    if (vad.isSpeech(buffer, AUDIO_BUF)) {
      ai.sendAudio((uint8_t*)buffer, len);
    }

    if (vad.shouldStop()) {
      listening = false; // tự dừng khi im lặng
    }
  }
}
