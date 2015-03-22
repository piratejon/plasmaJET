
#include "catch.hpp"

// #include "TttBoard.h"
#include "TttGame.h"
#include "AchiGame.h"

namespace {
  class TttTest : public ::testing::Test {
  };
}

TEST_CASE(TttTest, ValidateTestFramework) {
  ASSERT_EQ(0, 0);
}

/*
TEST_CASE(TttTest, TttBoardConstructor) {
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

TEST_CASE(TttTest, TttGameInit) {
  TttGame g;

  ASSERT_EQ(g.getTurnNumber(), 0);
  ASSERT_EQ(g.checkWinner(), false);
}

TEST_CASE(TttTest, TttGamePlaySanityCheck) {
  TttGame g;

  ASSERT_EQ(g.getTurnNumber(), 0);
  g.playMove(2);
  ASSERT_EQ(g.getTurnNumber(), 1);
  g.playMove(3);
  ASSERT_EQ(g.getTurnNumber(), 2);
}

TEST_CASE(TttTest, TttGameCopyConstructor) {
  TttGame g;

  ASSERT_EQ(g.getTurnNumber(), 0);
  g.playMove(2);
  g.playMove(0);
  g.playMove(3);
  ASSERT_EQ(g.getTurnNumber(), 3);

  // show equivalence after copy
  TttGame h(g);
  ASSERT_EQ(g.getTurnNumber(), 3);
  ASSERT_EQ(h.getTurnNumber(), 3);

  // show independence of src
  g.playMove(4);
  ASSERT_EQ(g.getTurnNumber(), 4);
  ASSERT_EQ(h.getTurnNumber(), 3);

  // show independence of dst
  h.playMove(7);
  h.playMove(8);
  h.playMove(1);
  ASSERT_EQ(g.getTurnNumber(), 4);
  ASSERT_EQ(h.getTurnNumber(), 6);
}

TEST_CASE(TttTest, TttAchiGameInheritedMembers) {
  AchiGame g;
  ASSERT_EQ(g.getTurnNumber(), 0);
  ASSERT_EQ(g.checkWinner(), false);

  g.playMove();
  ASSERT_EQ(g.getTurnNumber(), 1);

  AchiGame h(g);
  ASSERT_EQ(g.getTurnNumber(), 1);
  ASSERT_EQ(h.getTurnNumber(), 1);

  g.playMove();
  ASSERT_EQ(g.getTurnNumber(), 2);
  ASSERT_EQ(h.getTurnNumber(), 1);

  h.playMove();
  h.playMove();
  h.playMove();
  ASSERT_EQ(g.getTurnNumber(), 2);
  ASSERT_EQ(h.getTurnNumber(), 4);
}

TEST_CASE(TttTest, TttMinimaxBaseCase) {
  TttGame g;
  g.playMove(4); // x plays in the middle
  g.playMove(5); // o plays on the side -- DUMB!
  g.playMove(1); // x plays on the top
  g.playMove(7); // o tries to block -- DUMB!
  g.playMove(0); // x sets himself up for victory
  g.playMove(8); // o can block but it's too late
  
  // now x should figure out to play 2 to win
  ASSERT_EQ(g.computeNextMove(), 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

