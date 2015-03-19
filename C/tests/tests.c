
#include <string.h>

#include "tests.h"

#include "ttt.h"

void test_one(void) {
  ASSERT(1==1, "One failed to be equal to one.");
}

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

void test_final_position(void) {
  char b[] = "xxoo  xox";
  ASSERT(sizeof(b) == 10, "wrong sizeof(b)");

  ASSERT(ttt_winner(b) == ' ', "wrong winner identified");
}

void test_board_string_to_bitmask(void) {
  char b[] = "xxoo  xox";
  struct TttBoard t;
  ttt_board_from_string(b, &t);
  ASSERT(t.xs == 0x143, "wrong bitmask for xs");
  ASSERT(t.os == 0x08c, "wrong bitmask for os");
  ttt_string_increment(b, sizeof(b)-1);
  ASSERT(0 == strcmp(b, "oxoo  xox"), "wrong board after increment");
  //ASSERT(t.xs == 0x083, "wrong bitmask for xs");
  //ASSERT(t.os == 0x162, "wrong bitmask for os");
}

void do_tests(void) {
  TEST(test_one);
  TEST(test_increment_position);
  TEST(test_increment_string);
  TEST(test_final_position);
  TEST(test_board_string_to_bitmask);
}

