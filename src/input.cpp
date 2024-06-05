#include "Input.hpp"

Input::Input(XPT2046_Touchscreen* touchscreen) : touchscreen_(touchscreen) {}

// les mini delay pour menager le processeur
void Input::WaitForTouch() {
  while (!touchscreen_->tirqTouched() || !touchscreen_->touched()) delay(10);
}

void Input::WaitForTouchAndRelease() {
  while (!touchscreen_->tirqTouched() || !touchscreen_->touched()) delay(10);
  while (touchscreen_->touched()) delay(10);
}

void Input::WaitForRelease() {
  while (touchscreen_->touched()) delay(10);
}

int Input::Menu(Button* buttons, int buttonCount) {
  WaitForRelease();  // evité les miss clic
  int result = -1;
  int x, y, z;

  while (result == -1) {
    WaitForTouch();
    GetTouchCoordinates(x, y, z);  // void car je modifie la valeur depuis l'adresse de x, y, z
    result = DetectButtonPress(x, y, buttons, buttonCount);
    delay(10);
  }

  WaitForRelease();  // evité les miss clic
  return result;
}

void Input::GetTouchCoordinates(int& x, int& y, int& z) {
  TS_Point p = touchscreen_->getPoint();
  x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
  y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
  z = p.z;
}

int Input::DetectButtonPress(int x, int y, Button* buttons, int buttonCount) {
  for (int i = 0; i < buttonCount; ++i) {
    if (x >= buttons[i].x && x <= (buttons[i].x + buttons[i].w) && y >= buttons[i].y &&
        y <= (buttons[i].y + buttons[i].h)) {
      return i;
    }
  }
  return -1;
}