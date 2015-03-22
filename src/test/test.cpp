
#include <gtest/gtest.h>

// #include "TttBoard.h"
#include "TttGame.h"

namespace {
  class TttTest : public ::testing::Test {
  };
}

TEST_F(TttTest, ValidateTestFramework) {
  ASSERT_EQ(0, 0);
}

/*
TEST_F(TttTest, TttBoardConstructor) {
  TttBoard b1 = TttBoard(); // create empty board
  ASSERT_EQ(b.getSpace(0), ' ');
  ASSERT_EQ(b.getSpace(7), ' ');

  TttBoard b = TttBoard("xx oo xo "); // board with spots already
  ASSERT_EQ(b.getSpace(0), 'x');
  ASSERT_EQ(b.getSpace(4), 'o');
}

TEST(TttTest, TttBoardGetterSetter) {
  TttBoard b = TttBoard();

  // show that when we write to a space we can retrieve it
  b.setSpace(1, 'x');
  ASSERT_EQ(b.getSpace(1), 'x');

  // ... again
  b.setSpace(5, 'o');
  ASSERT_EQ(b.getSpace(5), 'o');

  // ensure that when we over-write something it sticks
  b.setSpace(5, 'x');
  ASSERT_EQ(b.getSpace(5), 'x');
}
*/

TEST(TttTest, TttGameInit) {
  TttGame g;

  ASSERT_EQ(g.getTurnNumber(), 0);
  ASSERT_EQ(g.checkWinner(), false);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

