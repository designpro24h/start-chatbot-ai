#pragma once
#include "../core/AppState.h"

class DisplayBase {
public:
  virtual void begin() = 0;
  virtual void showState(AppState state) = 0;
};
