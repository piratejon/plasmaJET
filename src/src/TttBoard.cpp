#include "TttBoard.h"

TttBoard::TttBoard() {
  int i;
//  for(i = 0; i < 10; i++) {
//    this->space[i] = 2;
//  }
}

//preconfigured board
TttBoard::TttBoard(const char *src) {

}

//Copied board
TttBoard::TttBoard(TttBoard &src) {

}

TttBoard &
TttBoard::operator=(const TttBoard &src) {

  return *this;
}

//last two functions share a unmade copy function

char
TttBoard::getSpace(int space) {
  char value;
//  switch(space) {
//    case 0 : value = space[0]; break;
//    case 1 : value = space[1]; break;
//    case 2 : value = space[2]; break;
//    case 3 : value = space[3]; break;
//    case 4 : value = space[4]; break;
//    case 5 : value = space[5]; break;
//    case 6 : value = space[6]; break;
//    case 7 : value = space[7]; break;
//    case 8 : value = space[8]; break;
//  }

  return 'a';
}

void
TttBoard::setSpace(int space, char player) {

//  case(player) {
//    case 'x' : this->space[space] = 0; 
//               break;
//    case 'o' : this->space[space] = 1;
//               break;
//  }

  return;
}

char
TttBoard::decodeSpace(TttSpace space) {
  char value;
//  case(space) {
//    case 0 : value = 'x';
//    case 1 : value = 'o';
//    case 2 : value = ' ';
//  }

  return 'a';
}

// look into when this is called to see where the value should be going
TttSpace
TttBoard::encodeSpace(char space) {
  TttSpace tttspace;
//  case(space) {
//    case 'x' : value = 0;
//    case 'y' : value = 1;
//    case ' ' : value = 2;
//  }

  return tttspace;
}
