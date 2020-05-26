#pragma once

#include <iostream>

enum class NoteKind {
  Normal,
  Hold,
  Hold_end,
  Circle,
  Circle_end,
  Quarter,
  Quarter_end
};

struct RowNote {
  NoteKind kind;
  unsigned long tick;
  unsigned char lane;
};

enum Timing { Perfect, Great, Good, Bad };

void addScore(Timing timing) { std::cout << (int)timing << std::endl; }