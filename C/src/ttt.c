
#include "ttt.h"

char ttt_position_increment(char p) {
  if (p == ' ') return 'x';
  if (p == 'x') return 'o';
  if (p == 'o') return ' ';
  return -1;
}

void ttt_string_increment(char * s, size_t t) {
  size_t i;
  for (i = 0; i < t; i += 1) {
    s[i] = ttt_position_increment(s[i]);
    if (s[i] != ' ') break;
  }
}

bool check_mask(int b, int mask) {
  return (b & mask) == mask;
}

bool ttt_winner_bits(int b) {
  return
    check_mask(b, 0x0007)
    || check_mask(b, 0x0038)
    || check_mask(b, 0x01c0)
    || check_mask(b, 0x0124)
    || check_mask(b, 0x0092)
    || check_mask(b, 0x0049)
    || check_mask(b, 0x0111)
    || check_mask(b, 0x0054);
}

char ttt_winner(char * board) {
  return ' ';
}

void ttt_board_from_string(char * b, struct TttBoard * t) {
  size_t i;
  if (t) {
    t->xs = t->os = t->fs = 0;
    for (i = 0; b[i] != '\0'; i += 1) {
      if (b[i] == 'x') {
        t->xs |= (1 << i);
      } else if (b[i] == 'o') {
        t->os |= (1 << i);
      } else {
        t->fs |= (1 << i);
      }
    }
  }
}

bool ttt_is_position_open(struct TttBoard * t, size_t pos) {
  return check_mask(t->fs, pos);
}

