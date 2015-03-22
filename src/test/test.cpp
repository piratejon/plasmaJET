
#include <gtest/gtest.h>

// #include "TttBoard.h"
// #include "TttGame.h"

namespace {
  class TttTest : public ::testing::Test {
  };
}

TEST_F(TttTest, ValidateTestFramework) {
  ASSERT_EQ(0, 0);
}

TEST_F(TttTest, TttBoardConstructor) {
  TttBoard b = TttBoard("xx oo xo ");
  ASSERT_EQ(b.getSpace(0), 'x');
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

