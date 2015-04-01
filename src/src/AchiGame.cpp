
#include "AchiGame.h"

AchiGame::AchiGame() {
  this->score_base = 1000;
  this->space = -1;
}

char
AchiGame::playerByTurn() const {
  if (this->turnNumber & 1) {
    return 'o';
  } else {
    return 'x';
  }
}

void
AchiGame::updateBlankSpace() {
  if (this->turnNumber > 7) {
    this->space = this->computeBlankSpot();
  } else {
    this->space = -1;
  }
}

void
AchiGame::playMove(int i) {
  if (this->turnNumber < 8) {
    this->board.setSpace(i, this->playerByTurn());
  } else {
    this->board.setSpace(this->space, this->board.getSpace(i));
    this->board.setSpace(i, ' ');
  }
  this->turnNumber += 1;
  this->hasWinner = this->check_for_win();
  updateBlankSpace();
}

void
AchiGame::copy_from(const AchiGame & src) {
  TttGame::copy_from(src);
  this->space = src.space;
  this->score_base = src.score_base;
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
    if (this->board.getSpace(i) == ' ') blank = i;
  }
  return blank;
}

bool
AchiGame::isValidMove(int i) const {
  return board.getSpace(i) == this->playerByTurn() && this->achiAdjacent(i, this->getBlankSpot());
}

bool
AchiGame::achiAdjacent(int src, int dst) const {
  static const bool achi_adjacent[9][9] = {
    { false,  true, false,  true,  true, false, false, false, false }, // 0 adjacent to 1,3,4
    { false,  true,  true, false,  true, false, false, false, false }, // 1 adjacent to 1,2,4 
    { false,  true, false, false,  true,  true, false, false, false }, // 2 adjacent to 1,4,5
    { false,  true, false, false,  true, false,  true, false, false }, // 3 adjacent to 0,4,6
    {  true,  true,  true,  true,  true,  true,  true,  true,  true }, // 4 adjacent to everybody!
    { false, false,  true, false,  true, false, false, false,  true }, // 5 adjacent to 2,4,8
    { false, false, false,  true,  true, false, false,  true, false }, // 6 adjacent to 3,4,7
    { false, false, false, false,  true, false,  true, false,  true }, // 7 adjacent to 4,6,8
    { false, false, false, false,  true,  true, false,  true, false }, // 8 adjacent to 4,5,7
  };

  return src >= 0 && src < 9 && dst >= 0 && dst < 9 && achi_adjacent[src][dst];
}

int
AchiGame::computeNextMove() {
  return 7;
}

