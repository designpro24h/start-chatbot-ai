#pragma once

class Button {
  int pin;
public:
  Button(int gpio);
  void begin();
  bool pressed();
};
