#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <elapsedMillis.h>

#include "aPlayer.hpp"
#include "board.hpp"
#include "common.hpp"
#include "display.hpp"
#include "input.hpp"
#include "playerAI.hpp"
#include "playerHuman.hpp"
#include "settings.hpp"

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;
bool backMenu;

TFT_eSPI tft = TFT_eSPI();

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

elapsedMillis Timer1;
unsigned long Interval1 = 300;

Board board;
Settings settings;
Display* display;  // pointeur vers tft
Input* input;      // pointeur vers tft

// PlayerHuman p1(Cell::X, touchscreen);
// PlayerAI p2(Cell::O);
APlayer* p1 = new PlayerHuman(Cell::X, touchscreen);
APlayer* p2 = new PlayerAI(Cell::O);

void setup() {
  Serial.begin(115200);

  // Init touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(2);

  // Init tft
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  randomSeed(analogRead(0));

  // Initialiser Display avec un pointeur vers tft
  display = new Display(&tft);
  // Initialiser Input avec un pointeur vers touchscreen
  input = new Input(touchscreen);

  settings.startPlayer = p1;
  display->GameMenu();
}

void loop() {
  GameState gameState;
  APlayer* player;

  switch (input->Menu(buttonMenuJeu, 2)) {
    case 0:
      /* code jeu */
      settings.startPlayer = settings.StartPlayer(p1, p2);
      player = settings.StartPlayer(p1, p2);
      gameState = GameState::InGame;

      board.NewBoard();
      display->BoardShow(board, player);

      display->BoardShow(board, (player->GetCell() == p1->GetCell()) ? p2 : p1);
      delay(500);

      while (gameState == GameState::InGame) {
        if (Timer1 >= Interval1) {
          int playerMove = player->ChooseMove(board);
          input->WaitForRelease();

          board.WriteCell(playerMove, player->GetCell());
          display->BoardShow(board, player);

          if (board.DoesGameHaveAWinner()) {
            gameState = GameState::Victory;
          } else if (board.IsBoardFull()) {
            gameState = GameState::Draw;
          } else {
            player = (player->GetCell() == p1->GetCell()) ? p2 : p1;
          }

          Timer1 = 0;
        }
      }

      settings.UpdateLosePlayer(board, p1, p2);
      display->EndGame(gameState, board);

      input->WaitForRelease();          // si on a toujours un doigt sur l'écran, ça passe instantanément
      input->WaitForTouchAndRelease();  // on attend un clic pour quitter le jeu
      display->GameMenu();
      break;

    case 1:
      backMenu = false;
      display->SettingsMenu();
      while (!backMenu) {
        switch (input->Menu(buttonMenuSettings, 5)) {
          case 0:
            // settings.MenuOpponent(input, display, p2, touchscreen);
            display->MenuOpponent();
            input->MenuOpponent(p2);
            break;

          case 1:
            /* code start mode */
            break;

          case 4:
            backMenu = true;
            break;

          default:
            break;
        }

        // eviter un clignotement
        if(!backMenu) display->SettingsMenu();
      }
      input->WaitForRelease();
      display->GameMenu();
      break;

    default:
      break;
  }

  delay(20);
}
