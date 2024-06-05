#include "common.hpp"

int largeur = SCREEN_WIDTH - 2 * 30;
Button buttonMenuJeu[] = {
    {30, 100, largeur, 40, FONT_SIZE_MOYEN, "Jouer", TFT_BLACK, TFT_WHITE},
    {30, 160, largeur, 40, FONT_SIZE_MOYEN, "Parametres", TFT_BLACK, TFT_WHITE},
};

/*
1 2 3
4 5 6
7 8 9
*/
Button buttonJeu[] = {
    {0, OFFSET, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
    {TILE_SIZE, OFFSET, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
    {2 * TILE_SIZE, OFFSET, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
    {0, OFFSET + TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
    {TILE_SIZE, OFFSET + TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
    {2 * TILE_SIZE, OFFSET + TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
    {0, OFFSET + 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
    {TILE_SIZE, OFFSET + 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
    {2 * TILE_SIZE, OFFSET + 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, "", 0, 0},
};

// TODO - Difficulte IA -> adversert: humain, ia imbatable, ia forte, ...
Button buttonMenuSettings[] = {
    {30, 65, largeur, 40, FONT_SIZE_MOYEN, "Adversaire", TFT_BLACK, TFT_WHITE},
    {30, 115, largeur, 40, FONT_SIZE_MOYEN, "Start mode", TFT_BLACK, TFT_WHITE},
    {30, 165, largeur, 40, FONT_SIZE_MOYEN, "Couleur J1", TFT_BLACK, TFT_WHITE},
    {30, 215, largeur, 40, FONT_SIZE_MOYEN, "Couleur J2", TFT_BLACK, TFT_WHITE},
    {30, 265, largeur, 40, FONT_SIZE_MOYEN, "Retour ->", TFT_BLACK, TFT_WHITE},
};

Button buttonMenuOpponent[] = {
    {30, 15, largeur, 40, FONT_SIZE_MOYEN, "Humain", TFT_BLACK, TFT_WHITE},
    {30, 65, largeur, 40, FONT_SIZE_MOYEN, "AI imbattable", TFT_BLACK, TFT_WHITE},
    {30, 115, largeur, 40, FONT_SIZE_MOYEN, "AI forte", TFT_BLACK, TFT_WHITE},
    {30, 165, largeur, 40, FONT_SIZE_MOYEN, "AI intermediaire", TFT_BLACK, TFT_WHITE},
    {30, 215, largeur, 40, FONT_SIZE_MOYEN, "AI debutant", TFT_BLACK, TFT_WHITE},
    {30, 265, largeur, 40, FONT_SIZE_MOYEN, "Retour ->", TFT_BLACK, TFT_WHITE},
};