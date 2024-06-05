#ifndef INPUT_HPP
#define INPUT_HPP

#include <XPT2046_Touchscreen.h>

#include <common.hpp>

#include "board.hpp"

class Input {
 public:
  // Display() = default;
  Input(XPT2046_Touchscreen* touchscreen);
  void WaitForTouch();
  void WaitForTouchAndRelease();
  void WaitForRelease();
  int Menu(Button* buttons, int buttonCount);

 private:
  XPT2046_Touchscreen* touchscreen_;
  void GetTouchCoordinates(int& x, int& y, int& z);
  int DetectButtonPress(int x, int y, Button* buttons, int buttonCount);
};

#endif  // INPUT_HPP