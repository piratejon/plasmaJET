
#include "tests.h"

void test_one(void) {
  ASSERT(1==1, "One failed to be equal to one.");
}

void do_tests(void) {
  TEST(test_one);
}

