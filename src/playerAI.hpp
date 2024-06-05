#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <random>

#include "aPlayer.hpp"
#include "board.hpp"
#include "common.hpp"
#include "settings.hpp"

class PlayerAI : public APlayer {
 public:
  PlayerAI(Cell cell);

  int ChooseMove(Board board) override;

 private:
  int Minimax(Board board, int depth, bool isMaximizingPlayer, Cell player, int maxDepth);
  std::mt19937 rng;
};

#endif  // PLAYERAI_HPP
