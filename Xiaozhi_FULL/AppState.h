#pragma once
#include "Config.h"

class AppStateManager {
public:
  static void set(AppState s);
  static AppState get();
private:
  static AppState current;
};