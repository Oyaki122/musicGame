#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "Circle.h"
#include "Hold.h"
#include "Normal.h"
#include "Note.h"
#include "NoteChecker.h"
#include "Quarter.h"

unsigned char Quarter::previousInputLane;

constexpr unsigned char LANE_NUM = 1;

std::vector<std::shared_ptr<Note>> judgingNote;

int nextNotesIndex = 0;

unsigned long counter = 0;
unsigned long playTime() { return counter; }

RowNote rowNotes[] = {{NoteKind::Hold, 50, 0}, {NoteKind::Hold_end, 80, 0}};
size_t notesNum = sizeof(rowNotes) / sizeof(rowNotes[0]);

void addScore(Timing timing);

std::unique_ptr<Note> noteFactory(RowNote& note) {
  switch (note.kind) {
    case NoteKind::Normal:
      return std::unique_ptr<Note>(new Normal(note.lane, note.tick));
      break;
    case NoteKind::Hold:
      return std::unique_ptr<Note>(new Hold(note.lane, note.tick));
      break;
    case NoteKind::Hold_end:
      return std::unique_ptr<Note>(new Hold_end(note.lane, note.tick));
      break;
    case NoteKind::Quarter:
      return std::unique_ptr<Note>(new Quarter(note.lane, note.tick));
      break;
  }
}

void MusicGameJudge() {
  static std::unique_ptr<Note> tmp = nullptr;
  int bpm = 200;
  while (true) {
    RowNote note;
    if (tmp == nullptr) {
      if (nextNotesIndex >= notesNum) break;
      note = rowNotes[nextNotesIndex];
      tmp = noteFactory(note);
      nextNotesIndex++;
    }

    if (!tmp->mustStart(playTime())) break;

    if (tmp->isEndNote) {
      for (const auto& n : judgingNote) {
        n->checkEndNote(tmp->type, tmp->lane);
      }
      tmp.reset();
      continue;
    }
    judgingNote.push_back(std::move(tmp));
    tmp.reset();
  }

  for (unsigned char i = 0; i < judgingNote.size(); i++) {
    if (judgingNote[i]->tick == playTime()) setPressed();
    judgingNote[i]->update(playTime());
  }
  judgingNote.erase(
      std::remove_if(judgingNote.begin(), judgingNote.end(),
                     [](std::shared_ptr<Note> n) { return n->getMustPop(); }),
      judgingNote.end());
}

int main() {
  std::cout << "start" << std::endl;
  while (counter < 1000) {
    MusicGameJudge();
    counter++;
  }
}