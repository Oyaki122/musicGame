#pragma once

bool pressed = false;

void setPressed() { pressed = true; }

bool isPressed() {
  bool tmp = pressed;
  pressed = false;
  return tmp;
}
bool wasPressed() {
  bool tmp = pressed;
  pressed = false;
  return tmp;
}