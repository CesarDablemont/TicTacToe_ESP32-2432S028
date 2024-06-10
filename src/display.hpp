#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <TFT_eSPI.h>

#include <common.hpp>

#include "aPlayer.hpp"
#include "board.hpp"
#include "settings.hpp"

class Display {
 public:
  Display(TFT_eSPI* tft);
  void GameMenu();
  void drawButton(const Button& b);
  
  void ClearScreen();
  void Grid();
  void Turn(APlayer* player);
  void OneCell(Cell cell, int x, int y);
  void Cells(Board board);
  void BoardShow(Board board, APlayer* player);
  void ErasedCell(Board board);
  void Win(Board board);
  void EndGame(GameState gameState, Board board);

  void SettingsMenu();
  void MenuOpponent();

 private:
  TFT_eSPI* tft;
};

#endif  // DISPLAY_HPP