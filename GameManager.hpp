#pragma once
#include <Vector.h>
#include "pitches.h"
#include "pins.h"

enum GStates {
  GOOD, BAD, NEXT
};

class GameManager {
public:
  static constexpr int NR_COLS = 4;
  
  void init();
  bool genNew();
  GStates checkPattern(int idx);
  int getScore() { return colorsSeq.size(); }
  void playLast();
  void upSpeed();
  int getSpeed() { return speed; }
private:
  int speed = 1;
  void activateCol(int idx);
  void playPattern(const Vector<int>&);
  Vector<int> colorsSeq, currSeq;
  size_t currPos = 0;
  static constexpr int MAX_LEN = 250;
};