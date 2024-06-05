#ifndef COMMON_HPP
#define COMMON_HPP

#include <TFT_eSPI.h>

#include <cstdint>

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

// Screen info
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define OFFSET SCREEN_HEIGHT - SCREEN_WIDTH
#define TILE_SIZE SCREEN_WIDTH / 3

#define FONT_SIZE_PETIT 1
#define FONT_SIZE_MOYEN 2
#define FONT_SIZE_GRAND 4

enum class Cell { Empty, X, O };

enum class GameState { InGame, Victory, Draw };

enum class StartMode { P1, P2, Alternate, LastLose };

enum class AIDifficultyMode { Impossible, Hard, Intermediate, Easy };

// Définir les valeurs possibles de AIDifficultyMode dans un tableau
constexpr std::array<AIDifficultyMode, 4> aiDifficultyModeValues = {
    AIDifficultyMode::Impossible, AIDifficultyMode::Hard, AIDifficultyMode::Intermediate, AIDifficultyMode::Easy};

// Buttons
struct Button {
  int x;
  int y;
  int w;
  int h;
  int fontSize;
  const char* text;
  uint16_t fgColor;
  uint16_t bgColor;
};

extern Button buttonMenuJeu[];
extern Button buttonJeu[];
extern Button buttonMenuSettings[];
extern Button buttonMenuOpponent[];

#endif  // COMMON_HPP
