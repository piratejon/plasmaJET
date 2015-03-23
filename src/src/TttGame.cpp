
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

  if (this->hasWinner) return best_move;

  for (i = 0; i < 9; i += 1) {
    if (board.getSpace(i) == ' ') {
      TttGame tmp(*this);
      int tmp_score;

      tmp.playMove(i);

      tmp_score = this->minimax();

      if (tmp.getTurnNumber() & 1) { // odd = O, minimize
        if (best_score > tmp_score) {
          best_score = tmp_score;
          best_move = i;
        }
      } else { // even = X, maximize
        if (best_score < tmp_score) {
          best_score = tmp_score;
          best_move = i;
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

  // do we already have a winner? if so, don't move
  if (this->hasWinner) return best_move;

  for (i = 0; i < 9; i += 1) {
    if (board.getSpace(i) == ' ') {
      TttGame tmp(*this);
      int tmp_score;

      tmp.playMove(i);

      tmp_score = this->minimax();

      if (tmp.getTurnNumber() & 1) { // odd = O, minimize
        if (best_score > tmp_score) {
          best_score = tmp_score;
          best_move = i;
        }
      } else { // even = X, maximize
        if (best_score < tmp_score) {
          best_score = tmp_score;
          best_move = i;
        }
      }
    }
  }

  return best_move;
}

