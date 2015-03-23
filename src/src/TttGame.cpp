
#include <iostream>
#include "TttGame.h"

TttGame::TttGame() {
  this->turnNumber = 0;
  this->hasWinner = false;
}

TttGame::TttGame(TttGame &src) {
  this->turnNumber = src.turnNumber;
  this->hasWinner = src.hasWinner;
  this->board = src.board;
}

int
TttGame::getTurnNumber() {
  return this->turnNumber;
}

bool
TttGame::checkWinner() {
  return this->hasWinner;
}

bool
TttGame::check_for_win() {
  if (board.getSpace(0) == 'x' || board.getSpace(0) == 'o') {
    if (board.getSpace(0) == board.getSpace(1) && board.getSpace(1) == board.getSpace(2)) return true; // 012
    if (board.getSpace(0) == board.getSpace(3) && board.getSpace(3) == board.getSpace(6)) return true; // 036
    if (board.getSpace(0) == board.getSpace(4) && board.getSpace(4) == board.getSpace(8)) return true; // 048
  }

  if (board.getSpace(1) == 'x' || board.getSpace(1) == 'o') {
    if (board.getSpace(1) == board.getSpace(4) && board.getSpace(4) == board.getSpace(7)) return true; // 147
  }

  if (board.getSpace(2) == 'x' || board.getSpace(2) == 'o') {
    if (board.getSpace(2) == board.getSpace(5) && board.getSpace(5) == board.getSpace(8)) return true; // 258
    if (board.getSpace(2) == board.getSpace(4) && board.getSpace(4) == board.getSpace(6)) return true; // 246
  }

  if (board.getSpace(3) == 'x' || board.getSpace(3) == 'o') {
    if (board.getSpace(3) == board.getSpace(4) && board.getSpace(4) == board.getSpace(5)) return true; // 345
  }

  if (board.getSpace(6) == 'x' || board.getSpace(6) == 'o') {
    if (board.getSpace(6) == board.getSpace(7) && board.getSpace(7) == board.getSpace(8)) return true; // 678
  }

  return false;
}

void
TttGame::playMove(int p) {

  if (this->turnNumber & 1) { // odd, O
    board.setSpace(p, 'o');
  } else { // even, X
    board.setSpace(p, 'x');
  }

  hasWinner = check_for_win();

  this->turnNumber += 1;
}

int
TttGame::minimax() {
  int i;
  int best_move = -1;
  int best_score = 0;

  if (this->hasWinner) {
    if (this->turnNumber & 1) { // it's O's turn, so X won
      best_score = 10 - turnNumber;
      std::cout << "mm" << this->turnNumber << " X won with score=" << best_score << "\n";
      return best_score;
    } else { // it is X's turn so O won
      best_score = turnNumber - 10 + 1;
      std::cout << "mm" << this->turnNumber << " O won with score=" << best_score << "\n";
      return best_score;
    }
  }

  for (i = 0; i < 9; i += 1) {
    if (board.getSpace(i) == ' ') {
      TttGame tmp(*this);
      int tmp_score;

      tmp.playMove(i);

      std::cout << "mm" << this->turnNumber << "; calling mm move=" << i << "\n";
      tmp_score = tmp.minimax();

      if (tmp.getTurnNumber() & 1) { // odd = O, minimize
        if (best_score < tmp_score) {
          best_score = tmp_score;
          best_move = i;
          std::cout << "mm" << this->turnNumber << "updated best_move=" << best_move << ", best_score=" << best_score << "\n";
        }
      } else { // even = X, maximize
        if (best_score > tmp_score) {
          best_score = tmp_score;
          best_move = i;
          std::cout << "mm" << this->turnNumber << "updated best_move=" << best_move << ", best_score=" << best_score << "\n";
        }
      }
    }
  }

  return best_score;
}

int
TttGame::computeNextMove() {
  int i;
  int best_move = -1;
  int best_score = 0; // worse for either max (pos) or min (neg)

  // do we already have a winner? shouldn't have called us if so!
  // if (this->hasWinner) return best_move;

  for (i = 0; i < 9; i += 1) {
    if (board.getSpace(i) == ' ') {
      TttGame tmp(*this);
      int tmp_score;

      tmp.playMove(i);

      std::cout << "cm" << this->turnNumber << "; calling mm move=" << i << "\n";

      tmp_score = tmp.minimax();

      if (tmp.getTurnNumber() & 1) { // odd = O, minimize
        if (best_score < tmp_score) {
          best_score = tmp_score;
          best_move = i;
          std::cout << "cm" << this->turnNumber << " updated best_move=" << best_move << ", best_score=" << best_score << "\n";
        } else {
          std::cout << "cm" << this->turnNumber << " did not update best_move=" << best_move << ", best_score=" << best_score << "\n";
        }
      } else { // even = X, maximize
        if (best_score > tmp_score) {
          best_score = tmp_score;
          best_move = i;
          std::cout << "cm" << this->turnNumber << " updated best_move=" << best_move << ", best_score=" << best_score << "\n";
        } else {
          std::cout << "cm" << this->turnNumber << " did not update best_move=" << best_move << ", best_score=" << best_score << "\n";
        }
      }
    }
  }

  return best_move;
}

