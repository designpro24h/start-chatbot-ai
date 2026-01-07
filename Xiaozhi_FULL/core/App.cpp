#include "App.h"
#include "../audio/VAD.h"

void App::begin() {
  mic.begin();
  speaker.begin();
  btnWake.begin();

  ai.begin(&speaker);
  display.begin();

  state = AppState::IDLE;
  display.showState(state);
}

void App::loop() {
  ai.loop();

  static int16_t buffer[AUDIO_BUF];
  size_t len = mic.read(buffer, sizeof(buffer));

  /* ===== WAKE ===== */
  if (btnWake.pressed() && state == AppState::IDLE) {
    vad.reset();
    ai.startListen();

    state = AppState::LISTENING;
    display.showState(state);
  }

  /* ===== LISTENING ===== */
  if (state == AppState::LISTENING) {

    if (vad.detect(buffer, AUDIO_BUF)) {

      if (vad.inSpeech()) {
        ai.sendAudio((uint8_t*)buffer, len);
      }

      if (vad.endSpeech()) {
        ai.finishListen();

        state = AppState::THINKING;
        display.showState(state);
      }
    }
  }

  /* ===== AI STATE ===== */
  if (ai.isSpeaking() && state != AppState::SPEAKING) {
    state = AppState::SPEAKING;
    display.showState(state);
  }

  if (ai.isIdle() && state != AppState::IDLE) {
    state = AppState::IDLE;
    display.showState(state);
  }
}
