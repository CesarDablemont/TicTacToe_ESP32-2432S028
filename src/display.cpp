#include "display.hpp"

Display::Display(TFT_eSPI* tft) : tft(tft) {}

void Display::GameMenu() {
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->drawCentreString("Tic Tac Toe", SCREEN_WIDTH / 2, 40, FONT_SIZE_GRAND);
  drawButton(buttonMenuJeu[0]);
  drawButton(buttonMenuJeu[1]);
}

void Display::drawButton(const Button& b) {
  tft->fillRect(b.x, b.y, b.w, b.h, b.bgColor);
  tft->setTextColor(b.fgColor, b.bgColor);
  tft->drawCentreString(b.text, b.x + (b.w / 2), b.y + (b.h / 2) - (3 * b.fontSize), b.fontSize);
}

/*========================================================================
---------------------------  JEU ----------------------
=========================================================================*/
#pragma region
void Display::Grid() {
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE);

  int cellSize = SCREEN_WIDTH / 3;
  int deltaY = SCREEN_HEIGHT - SCREEN_WIDTH;
  tft->drawRect(0, deltaY, SCREEN_WIDTH, SCREEN_WIDTH, TFT_WHITE);

  for (int i = 1; i < 3; i++) tft->drawLine(i * cellSize, deltaY, i * cellSize, SCREEN_WIDTH + deltaY, TFT_WHITE);

  for (int j = 1; j < 3; j++) tft->drawLine(0, j * cellSize + deltaY, SCREEN_WIDTH, j * cellSize + deltaY, TFT_WHITE);
}

void Display::Turn(APlayer* player) {
  if (player->theCell == Cell::O) {
    tft->setTextColor(Settings::PlayerColors[0]);
    tft->drawCentreString("Tour joueur 1", SCREEN_WIDTH / 2, 40, FONT_SIZE_GRAND);
  } else {
    tft->setTextColor(Settings::PlayerColors[1]);
    tft->drawCentreString("Tour joueur 2", SCREEN_WIDTH / 2, 40, FONT_SIZE_GRAND);
  }
  //   WriteInColor(Board.PlayerColors[0], "Player 1 turn");
  // else
  //   WriteInColor(Board.PlayerColors[1], "Player 2 turn");
}

void Display::OneCell(Cell cell, int x, int y) {
  int halfSize = SCREEN_WIDTH / 6 - 20;
  int squareSize = SCREEN_WIDTH / 6 - 2;  // -2 pour éviter de mordre la grille
  int thickness = 2;                      // Épaisseur des lignes

  switch (cell) {
    case Cell::X:
      // Dessiner les deux lignes de la croix avec des rectangles inclinés
      for (int i = -thickness / 2; i <= thickness / 2; i++) {
        tft->drawLine(x - halfSize + i, y - halfSize, x + halfSize + i, y + halfSize, Settings::PlayerColors[0]);
        tft->drawLine(x - halfSize + i, y + halfSize, x + halfSize + i, y - halfSize, Settings::PlayerColors[0]);
      }
      break;

    case Cell::O:
      for (int i = 0; i < thickness; i++) {
        tft->drawCircle(x, y, halfSize - i, Settings::PlayerColors[1]);
        tft->drawCircle(x, y, halfSize + i, Settings::PlayerColors[1]);
      }
      break;

    default:
      tft->fillRect(x - squareSize, y - squareSize, 2 * squareSize, 2 * squareSize, TFT_BLACK);
      break;
  }
}

void Display::Cells(Board board) {
  for (int i = 0; i < 9; i++) {
    OneCell(board.BoardCell(i), buttonJeu[i].x + buttonJeu[i].w / 2, buttonJeu[i].y + buttonJeu[i].h / 2);
  }
}

void Display::BoardShow(Board board, APlayer* player) {
  Grid();
  Turn(player);
  Cells(board);
}

void Display::ErasedCell(Board board) {
  for (int i = 0; i < 3; i++) {
    int Case = board.WinningPlayerCells()[i];
    OneCell(Cell::Empty, buttonJeu[Case].x + buttonJeu[Case].w / 2, buttonJeu[Case].y + buttonJeu[Case].h / 2);
  }
}

void Display::Win(Board board) {
  Cell winner = board.BoardCell(board.WinningPlayerCells()[0]);
  String winnerStr = (winner == Cell::X) ? "X" : "O";
  String message = "Les " + winnerStr + " gagnent!";

  int numberOfExecutions = 10;
  for (int i = 0; i < numberOfExecutions; i++) {
    if (i % 2 != 0) {
      Grid();
      Cells(board);
      tft->setTextColor(TFT_WHITE);
      tft->drawCentreString(message, SCREEN_WIDTH / 2, 40, FONT_SIZE_GRAND);
    } else
      ErasedCell(board);

    delay(250);
  }
}

void Display::EndGame(GameState gameState, Board board) {
  if (gameState == GameState::Victory)
    Win(board);
  else {
    Grid();
    Cells(board);
    tft->setTextColor(TFT_WHITE);
    tft->drawCentreString("Egalite", SCREEN_WIDTH / 2, 40, FONT_SIZE_GRAND);
  }
}

#pragma endregion

/*========================================================================
---------------------------   Parametre ----------------------
=========================================================================*/

void Display::SettingsMenu() {
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->drawCentreString("Parametre", SCREEN_WIDTH / 2, 25, FONT_SIZE_GRAND);

  for (int i = 0; i < 5; i++) {
    drawButton(buttonMenuSettings[i]);
  }
}


void Display::MenuOpponent() {
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE);

  for (int i = 0; i < 6; i++) {
    drawButton(buttonMenuOpponent[i]);
  }
}
