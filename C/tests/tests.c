
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

  ASSERT(ttt_is_position_open(&t, 2), "2 missing from positions list");
  ASSERT(ttt_is_position_open(&t, 6), "6 missing from positions list");
  ASSERT(ttt_is_position_open(&t, 7), "7 missing from positions list");
  ASSERT(ttt_is_position_open(&t, 8), "8 missing from positions list");

  ASSERT(ttt_fetch_position(&t, 8) == 'x', "wrong tile at 8");
  ASSERT(ttt_fetch_position(&t, 7) == 'x', "wrong tile at 7");
  ASSERT(ttt_fetch_position(&t, 6) == ' ', "wrong tile at 6");
  ASSERT(ttt_fetch_position(&t, 5) == 'o', "wrong tile at 5");
  ASSERT(ttt_fetch_position(&t, 4) == 'o', "wrong tile at 4");
  ASSERT(ttt_fetch_position(&t, 3) == 'x', "wrong tile at 3");
  ASSERT(ttt_fetch_position(&t, 2) == ' ', "wrong tile at 2");
  ASSERT(ttt_fetch_position(&t, 1) == ' ', "wrong tile at 1");
  ASSERT(ttt_fetch_position(&t, 0) == ' ', "wrong tile at 0");
}

void test_board_position_setters(void) {
  struct TttBoard t;
  ttt_board_from_string("         ", &t);
  ASSERT(t.xs == 0, "xs should not be set");
  ASSERT(t.os == 0, "os should not be set");
  ASSERT(t.fs == 0x1ff, "should be entirely empty");

  ttt_set_x(&t, 3);
  ASSERT(ttt_fetch_position(&t, 3) == 'x', "position 3 should be x");

  ASSERT(t.os == 0, "os have wrong value prior to reset");
  ASSERT(t.xs == 0x020, "xs have wrong value prior to reset");
  ASSERT(t.fs == 0x1df, "fs have wrong value prior to reset");
  ttt_set_o(&t, 3);
  ASSERT(ttt_fetch_position(&t, 3) == 'o', "position 3 should be o");
  ttt_set_o(&t, 5);
  ASSERT(ttt_fetch_position(&t, 5) == 'o', "position 5 should be o");
}

void test_base_case_score(void) {
  struct TttBoard t;
  ttt_board_from_string("xxxoo    ", &t);
  ASSERT(ttt_winner(&t) == 'x', "wrong winner identified");
  ASSERT(ttt_board_score(&t) == 7, "wrong score determined");
}

void do_tests(void) {
  TEST(test_increment_position);
  TEST(test_increment_string);
  TEST(test_board_string_to_bitmask);
  TEST(test_winner_bits);
  TEST(test_set_open_positions);
  TEST(test_board_position_setters);
  TEST(test_base_case_score);
}

