#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <XPT2046_Touchscreen.h>

#include <array>

#include "aPlayer.hpp"
#include "board.hpp"
#include "common.hpp"
#include "display.hpp"
#include "input.hpp"
#include "playerAI.hpp"
#include "playerHuman.hpp"

class Settings {
 public:
  static StartMode startMode;
  static std::array<uint16_t, 2> PlayerColors;
  static AIDifficultyMode aiDifficultyMode;
  APlayer* startPlayer = nullptr;
  APlayer* losePlayer = nullptr;

  APlayer* StartPlayer(APlayer* p1, APlayer* p2);
  void UpdateLosePlayer(Board board, APlayer* p1, APlayer* p2);
  static int GetAIDifficultyModeIndex();
  // void MenuOpponent(Input* input, Display* display, APlayer*& p2, XPT2046_Touchscreen& touchscreen);
};

#endif  // SETTINGS_HPP