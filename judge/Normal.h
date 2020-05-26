#pragma once
#include <math.h>

#include "ButtonTest.h"
#include "Note.h"
#include "NoteChecker.h"

class Normal : public Note {
 public:
  Normal(const unsigned char lane, const unsigned long tick)
      : Note(lane, tick, NoteKind::Normal, false) {}
  void update(unsigned long nowTick) {
    if (isPressed()) {
      addScore(calcScore(nowTick));
      mustPop = true;
    } else {
      if (nowTick > tick + 40) {
        mustPop = true;
        addScore(Bad);
      }
    }
  }
  void checkEndNote(const NoteKind kind, const unsigned char lane) override {
    return;
  }
  bool getMustPop() { return mustPop; }
  bool mustPop = false;
  bool mustStart(unsigned long nowTick) { return nowTick >= tick - 40; }

 protected:
  Timing calcScore(unsigned long nowTick) {
    unsigned long difference = std::abs(static_cast<long>(nowTick - tick));
    if (difference < 20) {
      return Perfect;
    } else if (difference < 32) {
      return Great;
    } else if (difference < 40) {
      return Good;
    } else {
      return Bad;
    }
  }
};