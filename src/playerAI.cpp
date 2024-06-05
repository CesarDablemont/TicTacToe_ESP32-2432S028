#include "playerAI.hpp"

PlayerAI::PlayerAI(Cell cell) : APlayer(cell) {
  std::random_device rd;
  rng = std::mt19937(rd());
}

int PlayerAI::ChooseMove(Board board) {
  int bestMove = -1;
  int bestScore = std::numeric_limits<int>::min();
  std::uniform_int_distribution<int> dist(0, 2);  // Pour la randomisation entre 0 et 2 inclue
  int position = Settings::GetAIDifficultyModeIndex();
  int maxDepth = 9 - position;  // Ajuster la profondeur de recherche

  for (int i = 0; i < 9; i++) {
    if (board.BoardCell(i) == Cell::Empty) {
      // Essayer ce coup
      board.WriteCell(i, theCell);
      int score = Minimax(board, 0, false, theCell, maxDepth);
      board.WriteCell(i, Cell::Empty);  // Réinitialiser la case car on n'a pas
                                        // de copie du board

      // Mettre à jour le meilleur coup
      if (score > bestScore) {
        bestScore = score;
        bestMove = i;
      }
      // Si le score est équivalent, ajouter un peu de hasard
      else if (score == bestScore) {
        if (dist(rng) == 0 || bestMove == -1) {
          bestScore = score;
          bestMove = i;
        }
      }
    }
  }
  return bestMove;
}

int PlayerAI::Minimax(Board board, int depth, bool isMaximizingPlayer, Cell player, int maxDepth) {
  if (depth > maxDepth) return 0;

  Cell opponent = (player == Cell::X) ? Cell::O : Cell::X;

  if (board.IsWinningPlayer(player)) return 100 / (depth + 1);     // L'IA gagne
  if (board.IsWinningPlayer(opponent)) return -100 / (depth + 1);  // Le joueur gagne
  if (board.IsBoardFull()) return 0;                               // Match nul

  if (isMaximizingPlayer) {
    int bestScore = std::numeric_limits<int>::min();
    for (int i = 0; i < maxDepth; i++) {
      if (board.BoardCell(i) == Cell::Empty) {
        board.WriteCell(i, player);
        int score = Minimax(board, depth + 1, false, player, maxDepth);
        board.WriteCell(i, Cell::Empty);
        bestScore = std::max(bestScore, score);
      }
    }
    return bestScore;
  } else {
    int bestScore = std::numeric_limits<int>::max();
    for (int i = 0; i < maxDepth; i++) {
      if (board.BoardCell(i) == Cell::Empty) {
        board.WriteCell(i, opponent);
        int score = Minimax(board, depth + 1, true, player, maxDepth);
        board.WriteCell(i, Cell::Empty);
        bestScore = std::min(bestScore, score);
      }
    }
    return bestScore;
  }
}
