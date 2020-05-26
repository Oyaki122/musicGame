#pragma once

#include "ButtonTest.h"
#include "Note.h"
#include "NoteChecker.h"

class Quarter : public Note {
 public:
  Quarter(const unsigned char lane, const unsigned long tick)
      : Note(lane, tick, NoteKind::Quarter, false) {}
  void update(unsigned long nowTick) {
    if (previousInputLane == lane) return;
    if (isPressed()) {
      addScore(Good);
      previousInputLane = lane;
    }
  }
  bool mustStart(unsigned long nowTick) { return nowTick >= tick; }
  bool getMustPop() { return mustPop; }
  void checkEndNote(const NoteKind kind, const unsigned char lane) override {
    if (kind == NoteKind::Quarter_end && lane == this->lane) mustPop = true;
  }

  static unsigned char previousInputLane;

 private:
  bool mustPop = false;
};