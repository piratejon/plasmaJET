
#include <strings.h>
#include <string.h>

#include "tests.h"

#include "ttt.h"

void test_increment_position(void) {
  char a = ' ';
  ASSERT(ttt_position_increment(a) == 'x', "Position failed to increment properly.");
  ASSERT(ttt_position_increment('x') == 'o', "Position failed to increment properly.");
}

void test_increment_string(void) {
  char a[10] = "         ";
  ASSERT(sizeof(a) == 10, "bad sizeof");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "x        "), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "o        "), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, " x       "), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "xx       "), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "ox       "), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, " o       "), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "xo       "), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "oo       "), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "  x      "), "string failed to increment");

  strcpy(a, "oooooooox");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "        o"), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "x       o"), "string failed to increment");

  strcpy(a, " oooooooo");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "xoooooooo"), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(0 == strcmp(a, "ooooooooo"), "string failed to increment");
  ttt_string_increment(a, sizeof(a)-1);
  ASSERT(' ' == a[0], "bad increment");
  ASSERT(' ' == a[1], "bad increment");
  ASSERT(' ' == a[2], "bad increment");
  ASSERT(' ' == a[3], "bad increment");
  ASSERT(' ' == a[4], "bad increment");
  ASSERT(' ' == a[5], "bad increment");
  ASSERT(' ' == a[6], "bad increment");
  ASSERT(' ' == a[7], "bad increment");
  ASSERT(' ' == a[8], "bad increment");
  ASSERT(0 == strcmp(a, "         "), "string failed to increment");
}

void test_winner_bits(void) {
  struct TttBoard t;
  ttt_board_from_string("xxoo    x", &t);
  ASSERT(ttt_winner_bits(t.xs) == false, "bad winner bits");
  ttt_board_from_string("xxxo    o", &t);
  ASSERT(ttt_winner_bits(t.xs) == true, "bad winner bits");
  ttt_board_from_string("  oxxx  o", &t);
  ASSERT(ttt_winner_bits(t.xs) == true, "bad winner bits");
  ttt_board_from_string("  o   xxx", &t);
  ASSERT(ttt_winner_bits(t.xs) == true, "bad winner bits");
  ttt_board_from_string("x ox  x  ", &t);
  ASSERT(ttt_winner_bits(t.xs) == true, "bad winner bits");
  ttt_board_from_string("x o   x  ", &t);
  ASSERT(ttt_winner_bits(t.xs) == false, "bad winner bits");
  ttt_board_from_string("oxooxo x ", &t);
  ASSERT(ttt_winner_bits(t.xs) == true, "bad winner bits");
  ttt_board_from_string("oxxoxx  x", &t);
  ASSERT(ttt_winner_bits(t.xs) == true, "bad winner bits");
  ttt_board_from_string("x o xo  x", &t);
  ASSERT(ttt_winner_bits(t.xs) == true, "bad winner bits");
  ttt_board_from_string("o x xox o", &t);
  ASSERT(ttt_winner_bits(t.xs) == true, "bad winner bits");
}

void test_board_string_to_bitmask(void) {
  char b[] = "xxoo  xox";
  struct TttBoard t;
  ttt_board_from_string(b, &t);
  ASSERT(t.xs == 0x143, "wrong bitmask for xs");
  ASSERT(t.os == 0x08c, "wrong bitmask for os");
  ttt_string_increment(b, sizeof(b)-1);
  ASSERT(0 == strcmp(b, "oxoo  xox"), "wrong board after increment");
  ttt_board_from_string(b, &t);
  ASSERT(t.xs == 0x142, "wrong bitmask for xs");
  ASSERT(t.os == 0x08d, "wrong bitmask for os");
}

void test_set_open_positions(void) {
  struct TttBoard t;
  ttt_board_from_string("xx oox   ", &t);

  ASSERT(ttt_is_position_open(&t, 0) == false, "but we put x there");
  ASSERT(ttt_is_position_open(&t, 1) == false, "but we put x there");
  ASSERT(ttt_is_position_open(&t, 2), "2 missing from positions list");
  ASSERT(ttt_is_position_open(&t, 3) == false, "but we put o there");
  ASSERT(ttt_is_position_open(&t, 4) == false, "but we put o there");
  ASSERT(ttt_is_position_open(&t, 5) == false, "but we put x there");
  ASSERT(ttt_is_position_open(&t, 6), "6 missing from positions list");
  ASSERT(ttt_is_position_open(&t, 7), "7 missing from positions list");
  ASSERT(ttt_is_position_open(&t, 8), "8 missing from positions list");

  ttt_set(&t, 2, 'x');
  ASSERT(ttt_fetch_position(&t, 2) == 'x', "but we put x there");
  ASSERT(ttt_is_position_open(&t, 2) == false, "2 now has x");

  ttt_set_blank(&t, 2);

  ASSERT(ttt_fetch_position(&t, 0) == 'x', "wrong tile at 8");
  ASSERT(ttt_fetch_position(&t, 1) == 'x', "wrong tile at 7");
  ASSERT(ttt_fetch_position(&t, 2) == ' ', "wrong tile at 6");
  ASSERT(ttt_fetch_position(&t, 3) == 'o', "wrong tile at 5");
  ASSERT(ttt_fetch_position(&t, 4) == 'o', "wrong tile at 4");
  ASSERT(ttt_fetch_position(&t, 5) == 'x', "wrong tile at 3");
  ASSERT(ttt_fetch_position(&t, 6) == ' ', "wrong tile at 2");
  ASSERT(ttt_fetch_position(&t, 7) == ' ', "wrong tile at 1");
  ASSERT(ttt_fetch_position(&t, 8) == ' ', "wrong tile at 0");
}

void test_board_position_setters(void) {
  struct TttBoard t;
  char b[10] = {0};

  ttt_board_from_string("         ", &t);
  ttt_board_to_string(&t, b);
  ASSERT(0 == strcmp(b, "         "), "board should be empty");
  ASSERT(t.xs == 0, "xs should not be set");
  ASSERT(t.os == 0, "os should not be set");
  ASSERT(t.fs == 0x1ff, "should be entirely empty");

  ttt_set_x(&t, 0);
  ttt_board_to_string(&t, b);
  ASSERT(0 == strcmp(b, "x        "), "x should be at position 0");
  ASSERT(ttt_fetch_position(&t, 0) == 'x', "position 0 should be x");
  ttt_set_o(&t, 0);
  ttt_board_to_string(&t, b);
  ASSERT(0 == strcmp(b, "o        "), "x should be at position 0");
  ASSERT(ttt_fetch_position(&t, 0) == 'o', "position 0 should be x");

  ttt_set_x(&t, 3);
  ttt_board_to_string(&t, b);
  ASSERT(0 == strcmp(b, "o  x     "), "x should be at position 3");
  ASSERT(ttt_fetch_position(&t, 3) == 'x', "position 3 should be x");
  ttt_set_o(&t, 3);
  ttt_board_to_string(&t, b);
  ASSERT(0 == strcmp(b, "o  o     "), "o should be at position 3");
  ASSERT(ttt_fetch_position(&t, 3) == 'o', "position 0 should be x");
}

void test_base_case_score(void) {
  struct TttBoard t;
  ttt_board_from_string("xxxoo    ", &t);
  ASSERT(ttt_winner(&t) == 'x', "wrong winner identified");
  ASSERT(ttt_board_score(&t) == 5, "wrong score computed");

  ttt_board_from_string("xo ooxxox", &t);
  ASSERT(ttt_winner(&t) == 'o', "wrong winner identified");
  ASSERT(ttt_board_score(&t) == 2, "wrong score computed");
}

void test_count_bits(void) {
  int x = 0x01a5; // 0b0000_0001_1010_0101 = 5 bits
  ASSERT(count_bits(x) == 5, "wrong number of bits in 0x01a5");
  ASSERT(count_bits(0xff) == 8, "wrong number of bits in 255");
  ASSERT(count_bits(0x0fffffff) == 28, "wrong number of bits in 0x0fffffff");
}

void test_one_up_from_base(void) {
  struct TttBoard t;
  char b[10] = {0};
  ttt_board_from_string("xx ooxoxo", &t);
  
  // preconditions for the case solved here
  ASSERT(ttt_winner(&t) == ' ', "but there is no winner");
  ASSERT(ttt_board_score(&t) == 2, "wrong number of points for this board");

  /*
     pick next move will iterate through the open spaces for whose turn it is
     and see if that one would let them win.
     score is defined as number of free squares left at the end + 1.
     any next-winning-moves have the same score.
     */

  // the case, solved
  ASSERT(ttt_is_position_open(&t, 2) == true, "cannot see the hole in the board");
  ttt_set_x(&t, 2);
  ASSERT(ttt_is_position_open(&t, 2) == false, "found a hole where it shouldn't");
  ttt_set_blank(&t, 2);
  ASSERT(ttt_is_position_open(&t, 2) == true, "cannot see the hole in the board");
  ASSERT(ttt_pick_next_move(&t, 'x', 'o') == 2, "picked the wrong move");

  // harder case: "x    o xo" since o can win on the next turn
  //   harder because the move is necessitated not by an immediate win
  // x response is to block o: "x x  o xo"
  // o response is to block x: "xox  o xo"
  // x gains the upper hand:   "xox  oxxo"
  // o blocks but still loses: "xoxo oxxo" or "xox ooxxo"
  // followed by:              "xoXoXoXxo" or "XoxXooXxo" 

  // pick something where o has to block
  ttt_board_from_string("xx oox xo", &t);
  ASSERT(ttt_pick_next_move(&t, 'o', 'x') == 2, "o picked the wrong move and lost");

  // try that hard case now
  ttt_board_from_string("xoxo  x  ", &t);
  ASSERT(ttt_pick_next_move(&t, 'o', 'x') == 4, "o failed to block");

  ttt_board_from_string("         ", &t);
  ttt_board_to_string(&t, b); ASSERT(0 == strcmp(b, "         "), "board is wrong!");
  ASSERT(ttt_pick_next_move(&t, 'x', 'o') == 0, "found a best starting move");

  ttt_set_x(&t, 0);
  ttt_board_to_string(&t, b); ASSERT(0 == strcmp(b, "x        "), "board is wrong!");
  ASSERT(ttt_is_position_open(&t, 0) == false, "but we placed x there");
  ASSERT(ttt_fetch_position(&t, 0) == 'x', "x did not get placed");
  ASSERT(ttt_pick_next_move(&t, 'o', 'x') == 1, "wrong move, o");

  ttt_set_o(&t, 1);
  ttt_board_to_string(&t, b); ASSERT(0 == strcmp(b, "xo       "), "board is wrong!");
  ASSERT(ttt_is_position_open(&t, 0) == false, "but we placed x there");
  ASSERT(ttt_fetch_position(&t, 0) == 'x', "x did not get placed");
  ASSERT(ttt_fetch_position(&t, 1) == 'o', "o did not get placed");
  ASSERT(ttt_pick_next_move(&t, 'x', 'o') == 2, "wrong move, x");

  ttt_set_x(&t, 2);
  ttt_board_to_string(&t, b); ASSERT(0 == strcmp(b, "xox      "), "board is wrong!");

  ASSERT(ttt_pick_next_move(&t, 'o', 'x') == 3, "o will lose!");
  ttt_set_o(&t, 3);
  ttt_board_to_string(&t, b); ASSERT(0 == strcmp(b, "xoxo     "), "board is wrong!");

  ASSERT(ttt_pick_next_move(&t, 'x', 'o') == 4, "o will lose!");
  ttt_set_x(&t, 4);
  ttt_board_to_string(&t, b); ASSERT(0 == strcmp(b, "xoxox    "), "board is wrong!");

  ASSERT(ttt_pick_next_move(&t, 'o', 'x') == 6, "o will lose!");
  ttt_set_x(&t, 6);
  // ttt_board_to_string(&t, b); ASSERT(0 == strcmp(b, "xoxox    "), "board is wrong!");

  ttt_board_from_string(" x   xoox", &t);
  ttt_set_o(&t, 2);
  ttt_board_to_string(&t, b);
  ASSERT(0 == strcmp(b, " xo  xoox"), "wrong thing was inserted");
  /* | xo|
     |  x|
     |oox| */
  ASSERT(identify_minimax_best_move(&t, 'x', 'o') == 4, "x played wrong by minimax!");

  ttt_board_from_string(" x   xoox", &t);
  ttt_board_to_string(&t, b);
  ASSERT(0 == strcmp(b, " x   xoox"), "wrong thing was inserted");
  /* | x |
     |  x|
     |oox| */
  ASSERT(identify_minimax_best_move(&t, 'o', 'x') == 2, "o played wrong by minimax!");
}

void do_tests(void) {
  TEST(test_increment_position);
  TEST(test_increment_string);
  TEST(test_board_string_to_bitmask);
  TEST(test_winner_bits);
  TEST(test_set_open_positions);
  TEST(test_board_position_setters);
  TEST(test_base_case_score);
  TEST(test_count_bits);
  TEST(test_one_up_from_base);
}

