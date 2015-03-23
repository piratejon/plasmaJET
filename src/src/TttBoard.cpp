#include "TttBoard.h"

TttBoard::TttBoard() {
  int i;
  for(i = 0; i < 9; i++) {
    this->space[i] = Blank;
  }
}

//preconfigured board
TttBoard::TttBoard(const char *src) {
  int i;
  for(i = 0; i < 9; i++) {
    this->space[i] = encodeSpace(src[i]);
  }
}

//Copied board
TttBoard::TttBoard(TttBoard &src) {
  int i;
  for(i = 0; i < 9; i++) {
    this->space[i] = src.space[i];
  }
}

TttBoard &
TttBoard::operator=(const TttBoard &src) {
  int i;
  for(i = 0; i < 9; i++) {
    this->space[i] = src.space[i];
  }
  return *this;
}

char
TttBoard::getSpace(int space) {
  char value;
  switch(space) {
    case 0 : value = decodeSpace(this->space[0]); break;
    case 1 : value = decodeSpace(this->space[1]); break;
    case 2 : value = decodeSpace(this->space[2]); break;
    case 3 : value = decodeSpace(this->space[3]); break;
    case 4 : value = decodeSpace(this->space[4]); break;
    case 5 : value = decodeSpace(this->space[5]); break;
    case 6 : value = decodeSpace(this->space[6]); break;
    case 7 : value = decodeSpace(this->space[7]); break;
    case 8 : value = decodeSpace(this->space[8]); break;
  }

  return value;
}

void
TttBoard::setSpace(int space, char player) {

  switch(player) {
    case 'x' : this->space[space] = X; break;
    case 'o' : this->space[space] = O; break;
  }

  return;
}

char
TttBoard::decodeSpace(TttSpace space) {
  char value;
  switch(space) {
    case X : value = 'x'; break;
    case O : value = 'o'; break;
    case Blank : value = ' '; break;
  }

  return value;
}

TttSpace
TttBoard::encodeSpace(char space) {
  TttSpace tttspace;
  switch(space) {
    case 'x' : tttspace = X; break;
    case 'o' : tttspace = O; break;
    case ' ' : tttspace = Blank; break;
  }
  return tttspace;
}
