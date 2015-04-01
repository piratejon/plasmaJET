
#include "AchiGame.h"

AchiGame::AchiGame() {
  this->space = -1;
}

int
AchiGame::computeNextMove() {
  return 3;
}

void
AchiGame::playMove(int i) {
  if (this->turnNumber >= 7) {
    this->space = 4;
  } else {
    this->space = -1;
  }
  this->turnNumber += 1;
}

int
AchiGame::getEmptySquare() {
  return this->space;
}

void
AchiGame::copy_from(const AchiGame & src) {
  TttGame::copy_from(src);
  this->space = src.space;
}

AchiGame::AchiGame(const AchiGame & src) : TttGame(src) {
  copy_from(src);
}

AchiGame &
AchiGame::operator= (const AchiGame & src) {
  copy_from(src);
  return *this;
}

int
AchiGame::getBlankSpot() {
  return this->space;
}

