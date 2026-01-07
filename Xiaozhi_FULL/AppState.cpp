#include "AppState.h"

AppState AppStateManager::current = AppState::IDLE;

void AppStateManager::set(AppState s) {
  current = s;
}

AppState AppStateManager::get() {
  return current;
}
