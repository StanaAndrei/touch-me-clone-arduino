#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Screen {
public:
  Screen();
  virtual void setData(const char *const format, ...) final;
  virtual void setLayout(LiquidCrystal *lcd) = 0;
  void enableRender() { render = true; }
  void disableRender() { render = false; }
  inline bool shouldRender() { return render; }
private:
  constexpr static int LEN_MAX = 100;
  bool render;
protected:
  String data[LEN_MAX];
};