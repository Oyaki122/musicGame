#include <time.h>

#include <chrono>
#include <iostream>

class CRGB {
 public:
  int r = 0;
  int g = 0;
  int b = 0;

  CRGB() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
  }
  CRGB(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
  }
  int operator==(CRGB obj) {
    bool flag = (this->r == obj.r && this->g == obj.g) && this->b == obj.b;
    return flag ? 1 : 0;
  }
};  //多分こんな感じで実装されてる。。。？わからん。

CRGB leds[20];

class Led {
 private:
  long long counter = 0;   //描写した回数
  int timing_counter = 0;  //ノーツを降らした回数
  int draw_conter = 0;     //譜面を流した回数
  int speed;
  int LED_NUM;
  int FPS;
  int* timing;
  int timing_num;

 public:
  Led(int speed, int LED_NUM, int FPS, int* timing, int timing_num) {
    this->speed = speed;
    this->LED_NUM = LED_NUM;
    this->FPS = FPS;
    this->timing = timing;
    this->timing_num = timing_num;
  }

  void draw() {
    counter++;
    if (counter % speed == 0) {
      draw_conter++;
      for (int i = LED_NUM - 1; i > 0; i--) {
        leds[i] = leds[i - 1];
      }
      leds[0] = CRGB(0, 0, 0);
    }
    if (counter == timing[timing_counter]) {
      leds[0] = CRGB(255, 0, 0);
      timing_counter++;
    }
  }
  void check(int millis) {}
};

void calc(int& speed, int FPS, int* timing, int timing_num) {
  int Frame_per_second =
      1.0 * 1000 / FPS + 0.5;  // 0.5足して四捨五入できてるはず。。。たぶん
  speed = 1.0 * speed / Frame_per_second + 0.5;
  for (int i = 0; i < timing_num; i++) {
    timing[i] = 1.0 * timing[i] / Frame_per_second + 0.5;
  }
}

int main() {
  int speed = 500;  //変更可能にする 球/ms
  int LED_NUM = 20;
  int FPS = 60;
  int timing[] = {100, 150, 500, 1500};  //単位はms　
  int timing_num = 4;
  calc(speed, FPS, timing,
       timing_num);  //ここで、単位をmsからフレーム数に変える。
  Led timing_game(speed, LED_NUM, FPS, timing, timing_num);
  for (int i = 0; i < 600; i++) {
    if (i == 6) continue;
    timing_game.draw();
    // timing_game.check();
    for (int i = 0; i < LED_NUM; i++) {
      if (leds[i].r == 255) {
        std::cout << 1;
      } else {
        std::cout << 0;
      }
    }
    std::cout << std::endl;
  }
}