
#include "ttt.h"

char ttt_position_increment(char p) {
  if (p == ' ') return 'x';
  if (p == 'x') return 'o';
  if (p == 'o') return ' ';
  return -1;
}

void ttt_string_increment(char * s, size_t t) {
  s[0] = 'x';
  /*
  for (i = 0; i < t; i += 1) {
  }
  */
}

