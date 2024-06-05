#include "PlayerHuman.hpp"

#include "common.hpp"

PlayerHuman::PlayerHuman(Cell cell, XPT2046_Touchscreen& touchscreen) : APlayer(cell), touchscreen_(touchscreen) {}

int PlayerHuman::ChooseMove(Board board) {
  int x, y, z;
  int move = -1;

  do {
    if (touchscreen_.tirqTouched() && touchscreen_.touched()) {
      TS_Point p = touchscreen_.getPoint();

      // jsp pk ces valeurs mais ça marche
      x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
      y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
      z = p.z;

      for (int i = 0; i < 9; i++) {
        if (x >= buttonJeu[i].x && x <= (buttonJeu[i].x + buttonJeu[i].w) && y >= buttonJeu[i].y &&
            y <= (buttonJeu[i].y + buttonJeu[i].h)) {
          if (board.BoardCell(i) == Cell::Empty) move = i;
        }
      }
    }
  } while (move == -1);

  return move;
}
