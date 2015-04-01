
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
    if (this->turnNumber & 1) {
      this->board.setSpace(i, 'o');
    } else {
      this->board.setSpace(i, 'x');
    }

    if (this->space == -1) {
      this->space = this->computeBlankSpot();
    } else {
      this->space = i;
    }
  } else {
    if (this->turnNumber & 1) {
      this->board.setSpace(i, 'o');
    } else {
      this->board.setSpace(i, 'x');
    }
  }
  this->turnNumber += 1;
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
AchiGame::getBlankSpot() const {
  return this->space;
}

int
AchiGame::computeBlankSpot() const {
  int blank = -1, i;
  for (i = 0; i < 9; i += 1) {
    if (board.getSpace(i) == ' ') blank = i;
  }
  return blank;
}

