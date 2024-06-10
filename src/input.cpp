#include "input.hpp"

Input::Input(XPT2046_Touchscreen& touchscreen) : touchscreen_(touchscreen) {}

void Input::WaitForTouch() {
  while (!touchscreen_.tirqTouched() || !touchscreen_.touched()) delay(10);
}

void Input::WaitForTouchAndRelease() {
  while (!touchscreen_.tirqTouched() || !touchscreen_.touched()) delay(10);
  while (touchscreen_.touched()) delay(10);
}

void Input::WaitForRelease() {
  while (touchscreen_.touched()) delay(10);
}

int Input::Menu(Button* buttons, int buttonCount) {
  WaitForRelease();
  int result = -1;
  int x, y, z;

  while (result == -1) {
    WaitForTouch();
    GetTouchCoordinates(x, y, z);
    result = DetectButtonPress(x, y, buttons, buttonCount);
    delay(10);
  }

  WaitForRelease();
  return result;
}

void Input::GetTouchCoordinates(int& x, int& y, int& z) {
  TS_Point p = touchscreen_.getPoint();
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

void Input::MenuOpponent(APlayer*& p2) {
  switch (Menu(buttonMenuOpponent, 6)) {
    case 0:
      delete p2;
      p2 = new PlayerHuman(Cell::O, touchscreen_);
      break;

    case 1:
      delete p2;
      p2 = new PlayerAI(Cell::O);
      Settings::aiDifficultyMode = AIDifficultyMode::Impossible;
      break;

    case 2:
      delete p2;
      p2 = new PlayerAI(Cell::O);
      Settings::aiDifficultyMode = AIDifficultyMode::Hard;
      break;

    case 3:
      delete p2;
      p2 = new PlayerAI(Cell::O);
      Settings::aiDifficultyMode = AIDifficultyMode::Intermediate;
      break;

    case 4:
      delete p2;
      p2 = new PlayerAI(Cell::O);
      Settings::aiDifficultyMode = AIDifficultyMode::Easy;
      break;

    default:
      break;
  }
}
