
#include <iostream>
#include "TttGame.h"

TttGame::TttGame() {
  this->turnNumber = 0;
  this->hasWinner = false;
}

void
TttGame::copy_from(const TttGame &src) {
  this->turnNumber = src.turnNumber;
  this->hasWinner = src.hasWinner;
  this->board = src.board;
}

TttGame::TttGame(const TttGame &src) {
  copy_from(src);
}

TttGame &
TttGame::operator= (const TttGame &src) {
  copy_from(src);
  return *this;
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
TttGame::computeNextMove(int depth) {
  int i;
  int best_move = -1;
  int best_score = this->score();
  int tmp_score;

  if (!this->hasWinner) {
    for (i = 0; i < 9; i += 1) {
      if (board.getSpace(i) == ' ') {
        TttGame tmp(*this);
        tmp.playMove(i);

        tmp_score = tmp.computeNextMove(depth + 1);

        if (best_move == -1) {
          best_score = tmp_score;
          best_move = i;
        }

        if (this->getTurnNumber() & 1) { // odd = O, minimize
          if (tmp_score < best_score) {
            best_score = tmp_score;
            best_move = i;
          }
        } else { // even = X, maximize
          if (tmp_score > best_score) {
            best_score = tmp_score;
            best_move = i;
          }
        }
      }
    }
  }

  return depth == 0 ? best_move : best_score;
}

int
TttGame::score() {
  if (check_for_win()) {
    if (turnNumber & 1) { // X played last so they must have won
      return 10 - turnNumber;
    } else { // O played last so they must have won
      return turnNumber - 10;
    }
  }

  return 0;
}

