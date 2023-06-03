#pragma once
#include "Screen.hpp"
#include <LiquidCrystal.h>

static struct : public Screen {
  void setLayout(LiquidCrystal *lcd) override {
    lcd->clear();
    lcd->print("score: " + data[0]);
    lcd->setCursor(0, 1);
    lcd->print(data[1]);
  }
} scoreScreen;

static struct : public Screen {
  void setLayout(LiquidCrystal *lcd) override {
    lcd->setCursor(5, 1);
    lcd->print("GAME OVER!!!");
    lcd->setCursor(2, 2);
    lcd->print("press reset!");
  }
} lostScreen;

static struct : public Screen {
  void setLayout(LiquidCrystal *lcd) override {
    lcd->setCursor(0, 4);
    String hss = "highest score: " + data[0];
    lcd->print(hss);
    delay(2000);
    lcd->setCursor(0, 4);
    String cl = "";
    for (int i = hss.length(); i; i--) {
      cl += " ";
    }
    lcd->print(cl);
  }
} hiscoreScreen;

static struct : public Screen {
  void setLayout(LiquidCrystal *lcd) override {
    lcd->setCursor(0, 4);
    String hss = "speed: " + data[0];
    lcd->print(hss);
    delay(200);
    lcd->setCursor(0, 4);
    String cl = "";
    for (int i = hss.length(); i; i--) {
      cl += " ";
    }
    lcd->print(cl);
  }
} speedScreen;