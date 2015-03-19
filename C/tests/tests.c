
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
  ttt_string_increment(a, sizeof(a));
  ASSERT(0 == strcmp(a, "x        "), "string failed to increment");
  // ttt_string_increment(a);
  // ASSERT(0 == strcmp(a, "o        "), "string failed to increment");
}

void do_tests(void) {
  TEST(test_one);
  TEST(test_increment_position);
}

