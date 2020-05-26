#pragma once

#include "ButtonTest.h"
#include "Note.h"
#include "NoteChecker.h"

class Circle : public Note {
 public:
  Circle(const unsigned char lane, const unsigned long tick)
      : Note(lane, tick, NoteKind::Circle, false) {}
  void update(unsigned long nowTick) {
    if (!isPressed()) return;
    if (direction == NOTSET) {
      int difference = lane - prevLane;
      if (prevLane == 0xff) {
        prevLane = lane;
      } else if (lane == 4 && prevLane == 1) {
        direction = CCW;
        return;
      } else if (lane == 1 && prevLane == 4) {
        direction = CW;
        return;
      } else if (difference == 1) {
        direction = CW;
      } else if (direction == -1) {
        direction = CCW;
      }
      return;
    }
    if (direction == CW) {
      if (lane == prevLane + 1 || (lane == 1 && prevLane == 4)) {
        addScore(Timing::Good);
      }
    } else if (direction == CCW) {
      if (lane == prevLane - 1 || (lane == 4 && prevLane == 1)) {
        addScore(Timing::Good);
      }
    }

    prevLane = lane;
  }
  void checkEndNote(const NoteKind kind, const unsigned char lane) override {
    if (kind == NoteKind::Circle_end && lane == this->lane) mustPop = true;
  }
  bool mustStart(unsigned long nowTick) { return nowTick <= tick; }

 private:
  static enum Direction { CW, CCW, NOTSET } direction;
  static bool isInitialized;
  static unsigned char prevLane;
  bool mustPop = false;
};