#include "TttBoard.h"

TttBoard::TttBoard() {
  int i;
  for(i = 0; i < 9; i++) {
    this->space[i] = Blank;
  }
}

void
TttBoard::setFromString(const char (&s)[10]) {
  int i;
  for(i = 0; i < 9; i++) {
    this->space[i] = encodeSpace(s[i]);
  }
}

//preconfigured board
TttBoard::TttBoard(const char (&src)[10]) {
  this->setFromString(src);
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
TttBoard::getSpace(int space) const {
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
    case ' ' : this->space[space] = Blank; break;
  }

  return;
}

char
TttBoard::decodeSpace(TttSpace space) const {
  char value;
  switch(space) {
    case X : value = 'x'; break;
    case O : value = 'o'; break;
    case Blank : value = ' '; break;
  }

  return value;
}

TttSpace
TttBoard::encodeSpace(char space) const {
  TttSpace tttspace;
  switch(space) {
    case 'x' : tttspace = X; break;
    case 'o' : tttspace = O; break;
    case ' ' : tttspace = Blank; break;
  }
  return tttspace;
}

TttBoard &
TttBoard::operator= (const char (&s)[10]) {
  this->setFromString(s);
  return *this;
}

int
TttBoard::serialize() const {
  int s = 0, i;

  for (i = 0; i < 9; i += 1) {
    s <<= 2;
    switch(this->space[i]) {
      case X: s |= 3; break;
      case O: s |= 1; break;
      case Blank: break; // nothing!
    }
  }

  return s;
}

bool
TttBoard::operator== (const char (&s)[10]) const {
  int i;
  for (i = 0; i < 9; i += 1) {
    char c = this->decodeSpace(this->space[i]);
    if (c != s[i]) return false;
  }
  return true;
}

void
TttBoard::deserialize (int s) {
  int i;
  for (i = 0; i < 9; i += 1, s >>= 2) {
    if ((s & 3) == 3) this->space[i] = X;
    else if ((s & 1) == 1) this->space[i] = O;
    else this->space[i] = Blank;
  }
}

bool
TttBoard::operator== (const TttBoard & t) const {
  int i;
  for (i = 0; i < 9; i += 1) {
    if (this->space[i] != t.space[i]) {
      return false;
    }
  }
  return true;
}

bool
TttBoard::operator!= (const TttBoard & t) const {
  return !((*this) == t);
}

TttBoard::TttBoard (int s) {
  this->deserialize(s);
}

