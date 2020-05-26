#pragma once

#include <queue>

class Note {
 public:
  Note(const unsigned char lane, const unsigned long tick, NoteKind type,
       bool isEndNote)
      : lane(lane), tick(tick), type(type), isEndNote(isEndNote) {}
  virtual void update(unsigned long nowTick) = 0;
  virtual void checkEndNote(const NoteKind kind, const unsigned char lane) = 0;
  virtual bool mustStart(unsigned long nowTick) = 0;
  virtual bool getMustPop() = 0;
  const NoteKind type;

  const unsigned char lane;
  const unsigned long tick;
  const bool isEndNote;
};
