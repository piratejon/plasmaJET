
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

// #include "TttBoard.h"
#include "TttGame.h"
#include "AchiGame.h"

TEST_CASE("are we alive?", "[dummy]") {
  REQUIRE(0 == 0);
}

/*
TEST_CASE(TttTest, TttBoardConstructor) {
  TttBoard b1 = TttBoard(); // create empty board
  REQUIRE(b.getSpace(0) == ' ');
  REQUIRE(b.getSpace(7) == ' ');

  TttBoard b = TttBoard("xx oo xo "); // board with spots already
  REQUIRE(b.getSpace(0) == 'x');
  REQUIRE(b.getSpace(4) == 'o');
}

TEST(TttTest, TttBoardGetterSetter) {
  TttBoard b = TttBoard();

  // show that when we write to a space we can retrieve it
  b.setSpace(1, 'x');
  REQUIRE(b.getSpace(1) == 'x');

  // ... again
  b.setSpace(5, 'o');
  REQUIRE(b.getSpace(5) == 'o');

  // ensure that when we over-write something it sticks
  b.setSpace(5, 'x');
  REQUIRE(b.getSpace(5) == 'x');
}
*/

TEST_CASE("constructor initializes fields", "[TttGame]") {
  TttGame g;

  REQUIRE(g.getTurnNumber() == 0);
  REQUIRE(g.checkWinner() == false);
}

/*
TEST_CASE(TttTest, TttGamePlaySanityCheck) {
  TttGame g;

  REQUIRE(g.getTurnNumber() == 0);
  g.playMove(2);
  REQUIRE(g.getTurnNumber() == 1);
  g.playMove(3);
  REQUIRE(g.getTurnNumber() == 2);
}

TEST_CASE(TttTest, TttGameCopyConstructor) {
  TttGame g;

  REQUIRE(g.getTurnNumber() == 0);
  g.playMove(2);
  g.playMove(0);
  g.playMove(3);
  REQUIRE(g.getTurnNumber() == 3);

  // show equivalence after copy
  TttGame h(g);
  REQUIRE(g.getTurnNumber() == 3);
  REQUIRE(h.getTurnNumber() == 3);

  // show independence of src
  g.playMove(4);
  REQUIRE(g.getTurnNumber() == 4);
  REQUIRE(h.getTurnNumber() == 3);

  // show independence of dst
  h.playMove(7);
  h.playMove(8);
  h.playMove(1);
  REQUIRE(g.getTurnNumber() == 4);
  REQUIRE(h.getTurnNumber() == 6);
}

TEST_CASE(TttTest, TttAchiGameInheritedMembers) {
  AchiGame g;
  REQUIRE(g.getTurnNumber() == 0);
  REQUIRE(g.checkWinner() == false);

  g.playMove();
  REQUIRE(g.getTurnNumber() == 1);

  AchiGame h(g);
  REQUIRE(g.getTurnNumber() == 1);
  REQUIRE(h.getTurnNumber() == 1);

  g.playMove();
  REQUIRE(g.getTurnNumber() == 2);
  REQUIRE(h.getTurnNumber() == 1);

  h.playMove();
  h.playMove();
  h.playMove();
  REQUIRE(g.getTurnNumber() == 2);
  REQUIRE(h.getTurnNumber() == 4);
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
  REQUIRE(g.computeNextMove() == 2);
}
*/

/*
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/
