
#include "TttBoard.h"

TttBoard::TttBoard(const char * str) {
  int i = 0;
  for (i = 0; str && str[i] != '\0'; i += 1) {
    this->board[i] = str[i];
  }
}

char
TttBoard::at(const int i) {
  return board[i];
}

