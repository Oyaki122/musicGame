#include <windows.h>

#include <array>
#include <chrono>
#include <iostream>
#include <string>
const int lane_size = 4;
int special_status[lane_size];
std::array<int, lane_size> x;
enum note_type {
  normal_note = 1,
  hold_start = 2,
  hold_end = 3,
};
struct note {
  note_type type;
  int time;
  int lane;
};
note song[] = {{normal_note, 1000, 0}, {normal_note, 2000, 1},
               {normal_note, 3000, 2}, {normal_note, 4000, 3},
               {hold_start, 5000, 1},  {normal_note, 6000, 0},
               {hold_end, 7000, 1}};
std::array<int, lane_size> send_lane(int dif) {
  static int index = 0;  //今注目してるノーツのインデックス
  std::array<int, lane_size> send;
  for (int i = 0; i < lane_size; i++) {
    send[i] = 0;
  }
  int normal = lane_size;  // normal == lane_sizeなら何も入ってない
  if (index >= std::extent<decltype(song)>::value) {
    return send;
  }  //譜面が終わったかの判別
  note looking_note = song[index];
  if (dif >= looking_note.time) {
    switch (looking_note.type) {
      case normal_note:
        normal = looking_note.lane;
        break;
      case hold_start:
        special_status[looking_note.lane] = 2;
        break;
      case hold_end:
        special_status[looking_note.lane] = 0;
        break;
    }
    index++;
  }
  for (int i = 0; i < lane_size; i++) {
    send[i] = special_status[i];
  }
  if (normal != lane_size) {
    send[normal] = 1;
  }
  // 0-何もない 1-ノーマルノーツ 2-ホールドノーツ
  return send;
}
int main() {
  for (int i = 0; i < lane_size; i++) {
    special_status[i] = 0;
  }
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 100; i++) {
    auto now = std::chrono::system_clock::now();
    int dif = std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
                  .count();
    x = send_lane(dif);
    std::cout << dif << std::endl;
    for (int i = 0; i < lane_size - 1; i++) {
      std::cout << x[i] << ",";
    }
    std::cout << x[lane_size] << std::endl;
    Sleep(100);
  }
}