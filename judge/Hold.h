#pragma once

#include <math.h>

#include "ButtonTest.h"
#include "Note.h"
#include "NoteChecker.h"

class Hold : public Note {
 public:
  Hold(const unsigned char lane, const unsigned long tick)
      : Note(lane, tick, NoteKind::Hold, false) {
    pointCounterMax = 3600 / 120;
  }
  void update(unsigned long nowTick) {
    if (!isInitialized) {
      auto timing = calcScore(nowTick);
      if (isPressed()) {
        addScore(timing);
        isInitialized = true;
      } else {
        if (nowTick - tick < 0 && timing == Timing::Bad) {
          mustPop = true;
        }
      }
      return;
    }
    if (isPressed()) {
      pointCounter++;
      countFromRelease = 0;
      if (pointCounter >= pointCounterMax) {
        addScore(Good);
        pointCounter = 0;
      }
    } else {
      countFromRelease++;
      if (countFromRelease >= countFromReleaseMax) {
        addScore(Bad);
        countFromRelease = 0;
      }
    }
  }
  void checkEndNote(const NoteKind kind, const unsigned char lane) override {
    if (kind == NoteKind::Hold_end && lane == this->lane) {
      mustPop = true;
      std::cout << "hold end" << std::endl;
    }
  }
  bool mustStart(unsigned long nowTick) { return nowTick <= tick - 50; }
  bool getMustPop() { return mustPop; }

  static const int judgeStart = 10;
  static const int judgeEnd = 10;

 private:
  bool isInitialized = false;
  unsigned long countFromRelease = 0;
  unsigned char pointCounter;
  int pointCounterMax;
  int countFromReleaseMax = 20;
  bool mustPop = false;

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

class Hold_end : public Note {
 public:
  Hold_end(const unsigned char lane, const unsigned long tick)
      : Note(lane, tick, NoteKind::Hold_end, true) {}
  void update(unsigned long nowTick) {}
  void checkEndNote(const NoteKind kind, const unsigned char lane) {}
  bool mustStart(unsigned long nowTick) { return nowTick >= tick; }
  bool getMustPop() { return true; }
};