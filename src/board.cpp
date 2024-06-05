#include "board.hpp"

Board::Board() { NewBoard(); }

void Board::NewBoard() { board.fill(Cell::Empty); }

Cell Board::BoardCell(int position) const { return board[position]; }

void Board::WriteCell(int position, Cell value) { board[position] = value; }

bool Board::IsBoardFull() const {
  for (const auto& cell : board) {
    if (cell == Cell::Empty) return false;
  }
  return true;
}

bool Board::DoesGameHaveAWinner() const {
  // Check rows and columns
  for (int i = 0; i < 3; ++i) {
    if ((board[i] != Cell::Empty) && (board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]))
      return true;  // Vertical
    if ((board[i * 3] != Cell::Empty) && (board[i * 3] == board[i * 3 + 1]) && (board[i * 3 + 1] == board[i * 3 + 2]))
      return true;  // Horizontal
  }

  // Check diagonals
  if ((board[0] != Cell::Empty) && (board[0] == board[4]) && (board[4] == board[8])) return true;
  if ((board[2] != Cell::Empty) && (board[2] == board[4]) && (board[4] == board[6])) return true;

  return false;
}

bool Board::IsWinningPlayer(Cell cell) const {
  return DoesGameHaveAWinner() && (board[WinningPlayerCells()[0]] == cell);
}

std::array<int, 3> Board::WinningPlayerCells() const {
  // Check rows and columns
  for (int i = 0; i < 3; ++i) {
    if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] != Cell::Empty))
      return {i, i + 3, i + 6};  // Vertical
    if ((board[i * 3] == board[i * 3 + 1]) && (board[i * 3 + 1] == board[i * 3 + 2]) && (board[i * 3] != Cell::Empty))
      return {i * 3, i * 3 + 1, i * 3 + 2};  // Horizontal
  }

  // Check diagonals
  if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] != Cell::Empty)) return {0, 4, 8};
  if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] != Cell::Empty)) return {2, 4, 6};

  return {-1, -1, -1};  // No winning cells found
}