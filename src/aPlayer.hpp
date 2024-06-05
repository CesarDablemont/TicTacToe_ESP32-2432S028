#ifndef APLAYER_HPP
#define APLAYER_HPP

#include "board.hpp"  // Ajoutez cette ligne
#include "common.hpp"

// class Board; // Forward declaration of Board class

class APlayer {
 public:
  Cell theCell;

  APlayer(Cell cell) : theCell(cell) {}

  Cell GetCell() { return theCell; }

  Cell OtherCell(Cell cell) { return (cell == Cell::X) ? Cell::O : Cell::X; }

  virtual ~APlayer() {}
  virtual int ChooseMove(Board board) = 0;
};

#endif  // APLAYER_HPP
