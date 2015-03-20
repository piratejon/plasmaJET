
#if ! defined(_PLASMAJET_TTT_H)
#define _PLASMAJET_TTT_H

#include <stdbool.h>
#include <stddef.h>

struct TttBoard {
  int xs, os, fs;
};

char ttt_position_increment(char);
void ttt_string_increment(char *, size_t);
void ttt_board_from_string(char *, struct TttBoard *);
bool ttt_winner_bits(int);
void ttt_list_open_positions(char *, char *);
bool ttt_is_position_open(struct TttBoard *, size_t);
char ttt_fetch_position(struct TttBoard *, size_t);
void ttt_set_x(struct TttBoard *, size_t);
void ttt_set_o(struct TttBoard *, size_t);
void ttt_set_blank(struct TttBoard *, size_t);
void ttt_set(struct TttBoard *, size_t, char);
int ttt_board_score(struct TttBoard *);
char ttt_winner(struct TttBoard *);
int count_bits(int);
int ttt_pick_next_move(struct TttBoard *, char, char);
void ttt_board_to_string(struct TttBoard *, char *);

#endif // _PLASMAJET_TTT_H

