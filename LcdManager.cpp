#include "LcdManager.hpp"

LcdManager::LcdManager() {}

LcdManager::LcdManager(const int pins[], int cols, int lines) {
  lcd = new LiquidCrystal(
    pins[5], pins[4], pins[3], pins[2], pins[1], pins[0]
  );
  lcd->begin(cols, lines);
  lcd->print("WELCOME!!!");
}

void LcdManager::printScreen(Screen &screen) {
  if (!screen.shouldRender()) {
    return;
  }//*/
  screen.setLayout(lcd);
  screen.disableRender();
}//*/