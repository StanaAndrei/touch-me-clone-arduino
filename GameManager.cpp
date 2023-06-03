#include "GameManager.hpp"
constexpr int gameTones[] = { NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G5};

void GameManager::init() {
  static int _buffer[GameManager::MAX_LEN], _buffer2[GameManager::MAX_LEN];
  colorsSeq = Vector<int>(_buffer);
  currSeq = Vector<int>(_buffer2);
  genNew();
}

void GameManager::activateCol(int idx) {
  constexpr int SOUND_DUR = 350;
  tone(SPEAKER_PIN, gameTones[idx], SOUND_DUR);
  digitalWrite(LED_PINS[idx], HIGH);
  delay(SOUND_DUR);
  digitalWrite(LED_PINS[idx], LOW);
}

bool GameManager::genNew() {
  if (currPos == GameManager::MAX_LEN) {
    return false;
  }
  currPos = 0;
  int newCol = random(0, GameManager::NR_COLS);
  colorsSeq.push_back(newCol);
  playPattern(colorsSeq);
  return true;
}

void GameManager::playPattern(const Vector<int> &colorsSeq) {
  for (int col : colorsSeq) {
    activateCol(col);
    delay(275 / speed);
  }
}

GStates GameManager::checkPattern(int colorIdx) {
  activateCol(colorIdx);
  if (colorIdx == colorsSeq[currPos]) {
    currPos++;
    currSeq.push_back(colorIdx);
    if (currPos == colorsSeq.size()) {
      currSeq.clear();
      return GStates::NEXT;
    }
    return GStates::GOOD;
  }
  return GStates::BAD;
}

void GameManager::playLast() {
  playPattern(currSeq);
}

void GameManager::upSpeed() {
  const int MAX_SPEED = 10;
  speed = ((speed + 1) % (MAX_SPEED + 1));
  if (speed == 0) {
    speed = 1;
  }
}