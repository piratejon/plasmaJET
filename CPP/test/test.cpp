
#include <gtest/gtest.h>

#include "TttBoard.h"

namespace {
  class TttTest : public ::testing::Test {
  };
}

TEST_F(TttTest, BoardFromString) {
  TttBoard t = TttBoard("xx oo xox");
  ASSERT_EQ(t.at(0), 'x');
  ASSERT_EQ(t.at(1), 'x');
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

