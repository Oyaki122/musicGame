#pragma once

enum note_type {
  normal_note = 1,
  hold_start = 2,
  hold_end = 3,
};
struct note {
  note_type type;
  int time;
  int lane;
  int Id;
};