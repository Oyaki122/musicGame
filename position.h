#include <vector>

#include "common.h"
#include "draw.h"

namespace Position {
int speed;
std::vector<note> &notes; // type,time,lane,id
int index;
std::vector<note> drawing;
std::vector<note> specials;
int top_to_judge,
    lights_num; //上から判定まで届くのにかかる時間、上から判定までの球の数
void init(int _speed, std::vector<note> &_notes) {
    notes = _notes;
    speed = _speed;
    index = 0;
    drawing.clear();
    specials.clear();
    top_to_judge = speed * lights_num; //計算式あってるか不確か
}

void update(unsigned long nowTick) {
    updateDrawingList(nowTick);
    Draw::draw(drawing, specials);
}
void deleteNote(const int ID) {}
void updateDrawingList(unsigned long nowTick) {
    if(notes[index].time - top_to_judge >= nowTick) {
        drawing.push_back(notes[index]);
    }
    //伊藤
}
} // namespace Position