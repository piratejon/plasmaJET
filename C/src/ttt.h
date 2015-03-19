
#if ! defined(_PLASMAJET_TTT_H)
#define _PLASMAJET_TTT_H

#include <stddef.h>

struct TttBoard {
  int xs, os;
};

char ttt_position_increment(char);
void ttt_string_increment(char *, size_t);
char ttt_winner(char *);
void ttt_board_from_string(char *, struct TttBoard *);

#endif // _PLASMAJET_TTT_H

