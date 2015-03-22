
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
  this->turnNumber += 1;
}

int
TttGame::computeNextMove() {
  return 2;
}

