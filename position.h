#include <vector>

#include "common.h"
#include "draw.h"

namespace Position {
int speed;
std::vector<note>& notes;
int index;
std::vector<note> drawing;
std::vector<note> specials;

void init(int _speed, std::vector<note>& _notes) {
  notes = _notes;
  speed = _speed;
  index = 0;
  drawing.clear();
  specials.clear();
}

void update(unsigned long nowTick) {
  updateDrawingList(nowTick);
  Draw::draw(drawing, specials);
}
void deleteNote(const int ID) {}
void updateDrawingList(unsigned long nowTick) {
  //伊藤
}
}  // namespace Position