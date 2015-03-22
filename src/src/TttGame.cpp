
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

void
TttGame::playMove(int p) {

  if (this->turnNumber & 1) { // odd, O
  } else { // even, X
  }

  this->turnNumber += 1;
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
    }
  }
}

