
#include "TttGame.h"

TttGame::TttGame(TttBoard & b) {
  this->b = &b;
  player = 'x';
}

TttGame::TttGame(TttBoard & b, char p) {
  this->b = &b;
  this->player = p;
}

char
TttGame::turn() const {
  return this->player;
}

char
TttGame::winner() const {
  if (b->at(0) == 'x' || b->at(0) == 'o') {
    if (b->at(0) == b->at(1) && b->at(1) == b->at(2)) return b->at(0);
    if (b->at(0) == b->at(3) && b->at(3) == b->at(6)) return b->at(0);
    if (b->at(0) == b->at(4) && b->at(4) == b->at(8)) return b->at(0);
  } else if (b->at(1) == 'x' || b->at(1) == 'o') {
    if (b->at(1) == b->at(4) && b->at(4) == b->at(7)) return b->at(1);
  } else if (b->at(2) == 'x' || b->at(2) == 'o') {
    if (b->at(2) == b->at(5) && b->at(5) == b->at(8)) return b->at(2);
    if (b->at(2) == b->at(4) && b->at(4) == b->at(6)) return b->at(2);
  } else if (b->at(3) == 'x' || b->at(3) == 'o') {
    if (b->at(3) == b->at(4) && b->at(4) == b->at(5)) return b->at(3);
  } else if (b->at(6) == 'x' || b->at(6) == 'o') {
    if (b->at(6) == b->at(7) && b->at(7) == b->at(8)) return b->at(6);
  }
  return ' ';
}

