
#include <stdio.h>

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
  return 10 - (count_bits(t->xs) + count_bits(t->os));
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

void printdent(int i) {
  while ( i-- > 0 ) printf("    ");
}

void print_board(struct TttBoard * t, char player, int depth) {
  printdent(depth);printf("%c's turn\n", player);
  printdent(depth);printf("%c|%c|%c\n",
      ttt_fetch_position(t, 0),
      ttt_fetch_position(t, 1),
      ttt_fetch_position(t, 2));
      
      printdent(depth);printf("%c|%c|%c\n", 
      ttt_fetch_position(t, 3),
      ttt_fetch_position(t, 4),
      ttt_fetch_position(t, 5));
        
        printdent(depth);printf("%c|%c|%c\n",
      ttt_fetch_position(t, 6),
      ttt_fetch_position(t, 7),
      ttt_fetch_position(t, 8));
}

int minimax(struct TttBoard * t, char player, char opponent, int depth) {
  int best_move = -1, best_score = -10, i;
  int tmp_score;

  printdent(depth);printf("mm%d: minimax entered with depth=%d\n", depth, depth);
  print_board(t, player, depth);

  if (ttt_winner(t) == player) {
    printdent(depth);printf("mm%d: player (%c) winning\n", depth, player);
    best_move = -1;
    best_score = depth - 10;
  } else if (ttt_winner(t) == opponent) {
    printdent(depth);printf("mm%d: opponent (%c) winning\n", depth, opponent);
    best_move = -1;
    best_score = 10 - depth;
  } else {
    for (i = 0; i < 9; i += 1) {
      printdent(depth);printf("mm%d: checking position %d: ", depth, i);
      if (ttt_is_position_open(t, i)) {
        int mm_result;
        printf("open, %c->%d\n", player, i);
        ttt_set(t, i, player);
          mm_result = minimax(t, opponent, player, depth + 1);
          tmp_score = 0 - mm_result;
          printdent(depth);printf("mm%d: mm result when %d<-%c: %d\n", depth, i, player, mm_result);
          printdent(depth);printf("mm%d: %c tmp_score: %d\n", depth, player, tmp_score);
        ttt_set_blank(t, i);
        if (player == 'x' && tmp_score > best_score) {
          printdent(depth);printf("mm%d: %c->%d=%d better than %c->%d=%d\n", depth, player, i, tmp_score, player, best_move, best_score);
          best_score = tmp_score;
          best_move = i;
        } else if (player == 'o' && tmp_score < best_score) {
          printdent(depth);printf("mm%d: %c->%d=%d better than %c->%d=%d\n", depth, player, i, tmp_score, player, best_move, best_score);
          best_score = tmp_score;
          best_move = i;
        } else {
          printdent(depth);printf("mm%d: %c->%d=%d not better than %c->%d=%d\n", depth, player, i, tmp_score, player, best_move, best_score);
        }
      } else {
        printf("closed\n");
      }
    }
  }

  if (best_move == -1) {
    printdent(depth);printf("mm%d: FAILED TO FIND A BEST MOVE!\n", depth);
    // best_score = 0;
  } else {
    printdent(depth);printf("mm%d: minimax returing best score=%d with position=%d\n", depth, best_score, best_move);
  }
  return best_score;
}

int identify_minimax_best_move(struct TttBoard * t, char player, char opponent) {
  int depth = 10 - ttt_board_score(t);

  int best_move = -1, best_score = -10, i;
  int tmp_score;

  printdent(depth);printf("imbm starts; depth=*%d*\n", depth);
  print_board(t, player, depth);

  for (i = 0; i < 9; i += 1) {
    printdent(depth);printf("imbm: checking position %d: ", i);
    if (ttt_is_position_open(t, i)) {
      int mm_result;
      printf("open, %c->%d\n", player, i);
      ttt_set(t, i, player);
      tmp_score = mm_result = minimax(t, opponent, player, depth + 1);
      // tmp_score = 0 - mm_result;
      printdent(depth);printf("imbm mm result when %d<-%c: %d\n", i, player, mm_result);
      printdent(depth);printf("imbm %c tmp_score=%d\n", player, tmp_score);
      ttt_set_blank(t, i);
      if (player == 'x' && tmp_score > best_score) {
        printdent(depth);printf("imbm %c->%d=%d better than %c->%d=%d\n", player, i, tmp_score, player, best_move, best_score);
        best_score = tmp_score;
        best_move = i;
      } else if (player == 'o' && tmp_score < best_score) {
        printdent(depth);printf("imbm %c->%d=%d better than %c->%d=%d\n", player, i, tmp_score, player, best_move, best_score);
        best_score = tmp_score;
        best_move = i;
      } else {
        printdent(depth);printf("imbm %c->%d=%d not better than %c->%d=%d\n", player, i, tmp_score, player, best_move, best_score);
      }
    } else {
      printf("closed\n");
    }
  }

  printdent(depth);printf("imbm: found best move %d\n", best_move);

  return best_move;
}

