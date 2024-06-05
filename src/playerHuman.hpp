#ifndef PLAYERHUMAN_HPP
#define PLAYERHUMAN_HPP

#include "XPT2046_Touchscreen.h"  // Assurez-vous d'inclure la bibliothèque appropriée
#include "aPlayer.hpp"
#include "board.hpp"

class PlayerHuman : public APlayer {
 public:
  PlayerHuman(Cell cell, XPT2046_Touchscreen& touchscreen);

  int ChooseMove(Board board) override;

 private:
  XPT2046_Touchscreen& touchscreen_;
};

#endif  // PLAYERHUMAN_HPP
