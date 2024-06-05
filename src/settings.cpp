#include "settings.hpp"

// Initialize static members
StartMode Settings::startMode = StartMode::Alternate;
std::array<uint16_t, 2> Settings::PlayerColors = {TFT_RED, TFT_BLUE};
AIDifficultyMode Settings::aiDifficultyMode = AIDifficultyMode::Impossible;

APlayer* Settings::StartPlayer(APlayer* p1, APlayer* p2) {
  switch (startMode) {
    case StartMode::P1:
      return p1;
    case StartMode::P2:
      return p2;
    case StartMode::Alternate:
      return (startPlayer == p1) ? p2 : p1;
    case StartMode::LastLose:
      return (losePlayer == p1) ? p1 : p2;
    default:
      return p1;
  }
}

void Settings::UpdateLosePlayer(Board board, APlayer* p1, APlayer* p2) {
  if (board.IsWinningPlayer(p1->theCell))
    losePlayer = p2;
  else if (board.IsWinningPlayer(p2->theCell))
    losePlayer = p1;
  else
    losePlayer = (startPlayer == p1) ? p1 : p2;
}

int Settings::GetAIDifficultyModeIndex() {
  for (size_t i = 0; i < aiDifficultyModeValues.size(); ++i) {
    if (Settings::aiDifficultyMode == aiDifficultyModeValues[i]) {
      return static_cast<int>(i);
    }
  }
  return -1;  // Si la valeur n'est pas trouvée, retourner -1
}

// void Settings::MenuOpponent(Input* input, Display* display, APlayer*& p2, XPT2046_Touchscreen& touchscreen) {
//   switch (input->Menu(buttonMenuOpponent, 6)) {
//     case 0:
//       delete p2;
//       p2 = new PlayerHuman(Cell::O, touchscreen);
//       break;

//     case 1:
//       delete p2;
//       p2 = new PlayerAI(Cell::O);
//       aiDifficultyMode = AIDifficultyMode::Impossible;
//       break;

//     case 2:
//       delete p2;
//       p2 = new PlayerAI(Cell::O);
//       aiDifficultyMode = AIDifficultyMode::Hard;
//       break;

//     case 3:
//       delete p2;
//       p2 = new PlayerAI(Cell::O);
//       aiDifficultyMode = AIDifficultyMode::Intermediate;
//       break;

//     case 4:
//       delete p2;
//       p2 = new PlayerAI(Cell::O);
//       aiDifficultyMode = AIDifficultyMode::Easy;
//       break;

//     default:
//       break;
//   }

//   display->SettingsMenu();
// }
