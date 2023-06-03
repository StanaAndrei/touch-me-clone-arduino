#pragma once
#include <LiquidCrystal.h>
#include "Screen.hpp"

class LcdManager {
public:
  LcdManager();
  LcdManager(const int pins[], int cols, int lines);
  void printScreen(Screen &screen);
private:
  LiquidCrystal *lcd = nullptr;
};
