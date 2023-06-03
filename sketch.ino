#include <Wire.h>
#include <EEPROM.h>
#include "Button.hpp"
#include "LcdManager.hpp"
#include "pins.h"
#include "GameManager.hpp"
#include "UtilScreens.h"
#include "defines.h"

Button colBtns[GameManager::NR_COLS];
LcdManager lcdm;
GameManager gm;
Button highestBtn(HIGHEST_PIN), playLastBtn(PLAY_LAST_PIN), speedBtn(SPEED_PIN);

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  lcdm = LcdManager(LCD_PINS, 20, 4);
  pinMode(SPEAKER_PIN, OUTPUT);
  for (int i = 0; i < GameManager::NR_COLS; i++) {
    colBtns[i] = Button(COLOR_BTNS_PINS[i]);
    colBtns[i].begin();
  }
  delay(300);
  gm.init();
  scoreScreen.setData("s", "0");
  lcdm.printScreen(scoreScreen);
  highestBtn.begin();
  playLastBtn.begin();
  speedBtn.begin();
}

void loop() {
  for (int i = 0; i < GameManager::NR_COLS; i++) {
    if (colBtns[i].pressed()) {
      GStates gState = gm.checkPattern(i);
      if (gState == GStates::BAD) {
        lcdm.printScreen(lostScreen);
        delay(250);
        abort();
      } else if (gState == GStates::NEXT) {
        const int score = gm.getScore();
        scoreScreen.setData("i", score);
        lcdm.printScreen(scoreScreen);
        delay(750);
        EEPROM.write(HIGHEST_SCORE_ADR, MAX(score, EEPROM.read(HIGHEST_SCORE_ADR) % ((1 << 8) - 1)));
        bool canGen = gm.genNew();
        if (!canGen) {
          scoreScreen.setData("is", score, "(MAX SCORE REACHED!)");
          lcdm.printScreen(scoreScreen);
          delay(100);
          abort();
        }
      } else if (gState == GStates::GOOD) {
        //Serial.println("good!");
      }
    }
  }//*/

  if (highestBtn.pressed()) {
    byte val = EEPROM.read(HIGHEST_SCORE_ADR) % ((1 << 8) - 1);
    hiscoreScreen.setData("i", val);
    lcdm.printScreen(hiscoreScreen);
  } else if (playLastBtn.pressed()) {
    gm.playLast();
  } else if (speedBtn.pressed()) {
    gm.upSpeed();
    speedScreen.setData("i", gm.getSpeed());
    lcdm.printScreen(speedScreen);
  }
}
