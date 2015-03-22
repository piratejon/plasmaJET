
#include "TttBoard.h"

TttBoard::TttBoard(const char * str) {
  this->from_string(str);
}

char
TttBoard::at(const int i) const {
  return board[i];
}

void
TttBoard::set(const int i, const char c) {
  board[i] = c;
}

void
TttBoard::from_string(const char * str) {
  int i = 0;
  for (i = 0; str && str[i] != '\0'; i += 1) {
    this->board[i] = str[i];
  }
}

