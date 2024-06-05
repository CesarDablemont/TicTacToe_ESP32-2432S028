#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <common.hpp>

class Board {
 public:
  std::array<Cell, 9> board;

  Board();

  void NewBoard();
  Cell BoardCell(int position) const;
  void WriteCell(int position, Cell value);

  bool IsBoardFull() const;
  bool DoesGameHaveAWinner() const;
  bool IsWinningPlayer(Cell cell) const;
  std::array<int, 3> WinningPlayerCells() const;
};

#endif  // BOARD_HPP
