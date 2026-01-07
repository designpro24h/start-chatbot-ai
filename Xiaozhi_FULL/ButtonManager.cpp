#include "ButtonManager.h"
#include "Config.h"
#include <Arduino.h>

void ButtonManager::init() {
  pinMode(PIN_WAKE, INPUT_PULLUP);
  pinMode(PIN_VOL_UP, INPUT_PULLUP);
  pinMode(PIN_VOL_DN, INPUT_PULLUP);
}

bool ButtonManager::wakePressed() {
  return digitalRead(PIN_WAKE) == LOW;
}
