#pragma once

class DisplayBase {
public:
  virtual void begin() = 0;
  virtual void showStatus(const char* msg) = 0;
};
