
#include "tests.h"

#include "ttt.h"

void test_one(void) {
  ASSERT(1==1, "One failed to be equal to one.");
}

void test_increment_position(void) {
  char a = ' ';
  ASSERT(ttt_position_increment(a) == 'x', "Position failed to increment properly.");
}

void do_tests(void) {
  TEST(test_one);
}

