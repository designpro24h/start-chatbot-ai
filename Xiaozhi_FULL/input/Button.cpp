#include "Button.h"
#include <Arduino.h>

Button::Button(int gpio) : pin(gpio) {}

void Button::begin() {
  pinMode(pin, INPUT_PULLUP);
}

bool Button::pressed() {
  return digitalRead(pin) == LOW;
}
