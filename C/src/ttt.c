
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

bool check_bit(int b, int p) {
  return (b & (1 << p)) != 0;
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

char ttt_winner(struct TttBoard * t) {
  if (ttt_winner_bits(t->xs)) return 'x';
  if (ttt_winner_bits(t->os)) return 'o';
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
  return check_bit(t->fs, pos);
}

char ttt_fetch_position(struct TttBoard * t, size_t pos) {
  if (check_bit(t->xs, pos)) return 'x';
  else if (check_bit(t->os, pos)) return 'o';
  else return ' ';
}

void ttt_set_x(struct TttBoard * t, size_t pos) {
  t->xs |= (1 << pos);
  t->os &= ~(1 << pos);
  t->fs &= ~(1 << pos);
}

void ttt_set_o(struct TttBoard * t, size_t pos) {
  t->xs &= ~(1 << pos);
  t->os |= (1 << pos);
  t->fs &= ~(1 << pos);
}

void ttt_set_blank(struct TttBoard * t, size_t pos) {
  t->xs &= ~(1 << pos);
  t->os &= ~(1 << pos);
  t->fs |= (1 << pos);
}
void ttt_set(struct TttBoard * t, size_t pos, char w) {
  if (w == 'x') {
    ttt_set_x(t, pos);
  } else if (w == 'o') {
    ttt_set_o(t, pos);
  } else {
    ttt_set_blank(t, pos);
  }
}

int ttt_board_score(struct TttBoard * t) {
  return count_bits(t->fs) + 1;
}

int ttt_game_score(struct TttBoard * t, char player, char opponent) {
  char winner = ttt_winner(t);
  if (winner == player) return 10 - ttt_board_score(t);
  if (winner == opponent) return ttt_board_score(t) - 10;
  return 0;
}

int count_bits(int x) {
  int count;
  for ( count = 0; (x & 0xffffffff) != 0; x >>= 1 ) {
    count += (x & 1);
  }
  return count;
}

int ttt_pick_next_move(struct TttBoard * _t, char player, char opponent) {
  int i;
  struct TttBoard t2 = {.xs = _t->xs, .os = _t->os, .fs = _t->fs};
  struct TttBoard * t = &t2;

  // can we win from here?
  for ( i = 0; i < 9; i += 1 ) {
    if ( ttt_is_position_open(t, i) ) {
      ttt_set(t, i, player);
      if (ttt_winner(t) == player) {
        ttt_set_blank(t, i);
        return i;
      }
      ttt_set_blank(t, i);
    }
  }

  // might we lose from here?
  for ( i = 0; i < 9; i += 1 ) {
    if ( ttt_is_position_open(t, i) ) {
      ttt_set(t, i, opponent);
      // opponent will win so we have to play here
      if (ttt_winner(t) == opponent) {
        ttt_set_blank(t, i);
        return i;
      }
      ttt_set_blank(t, i);
    }
  }

  // if neither of those things then i guess we brute force
  int best_score = 0, best_position = 0;
  for ( i = 0; i < 9; i += 1 ) {
    if ( ttt_is_position_open(t, i) ) {
      int tmp_opponent_move, tmp_score;
      ttt_set(t, i, player); // we shouldn't win because of the first loop
        tmp_opponent_move = ttt_pick_next_move(t, opponent, player);
        tmp_score = ttt_board_score(t);
        if (ttt_winner(t) == opponent) tmp_score = 0 - tmp_score;
        ttt_set(t, tmp_opponent_move, opponent);
          if (tmp_score > best_score) {
            best_score = tmp_score;
            best_position = i;
          }
        ttt_set_blank(t, tmp_opponent_move);
      ttt_set_blank(t, i);
    }
  }

  // couldn't find a move, what?
  return best_position;
}

void ttt_board_to_string(struct TttBoard * t, char * s) {
  s[0] = ttt_fetch_position(t, 0);
  s[1] = ttt_fetch_position(t, 1);
  s[2] = ttt_fetch_position(t, 2);
  s[3] = ttt_fetch_position(t, 3);
  s[4] = ttt_fetch_position(t, 4);
  s[5] = ttt_fetch_position(t, 5);
  s[6] = ttt_fetch_position(t, 6);
  s[7] = ttt_fetch_position(t, 7);
  s[8] = ttt_fetch_position(t, 8);
}

int _fake_score(struct TttBoard * t, char player, char opponent, int depth) {
  if (ttt_winner(t) == player) return 10 - depth;
  if (ttt_winner(t) == opponent) return depth - 10;
  return 0;
}

int minimax(struct TttBoard * t, char player, char opponent, int depth) {
  int best_score = 0, best_move = 0, i;
  struct TttBoard t2;

  int score_stack[10] = {-1};
  int position_stack[10] = {-1};

  if (depth == 9) {
    // game over
    best_move = -1;
  } else {
    int tmp_score = 0, tmp_move = 0;
    for (i = 0; i < 9; i += 1) {
      t2.xs = t->xs;
      t2.os = t->os;
      t2.fs = t->fs;
      if (ttt_is_position_open(&t2, i)) {
        ttt_set(&t2, i, player);
        tmp_move = minimax(&t2, opponent, player, depth + 1);
        ttt_set(&t2, tmp_move, opponent);
        tmp_score = _fake_score(&t2, opponent, player, depth + 1);
        if (tmp_score > best_score) {
          best_score = tmp_score;
          best_move = tmp_move;
        }
      }
    }
  }

  return best_move;
}

