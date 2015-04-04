
#include "catch.hpp"

#include "TttBoard.h"
#include "TttGame.h"
#include "AchiGame.h"

TEST_CASE("are we alive?", "[dummy]") {
  REQUIRE(0 == 0);
}

TEST_CASE("encodes and decodes space identifiers", "[TttBoard]") {
  TttBoard b;
  REQUIRE(b.encodeSpace(' ') == Blank);
  REQUIRE(b.encodeSpace('x') == X);
  REQUIRE(b.encodeSpace('o') == O);

  REQUIRE(b.decodeSpace(X) == 'x');
  REQUIRE(b.decodeSpace(O) == 'o');
  REQUIRE(b.decodeSpace(Blank) == ' ');
}

TEST_CASE("constructs a TttBoard", "[TttBoard]") {
  TttBoard b1; // create empty board
  REQUIRE(b1.getSpace(0) == ' ');
  REQUIRE(b1.getSpace(7) == ' ');

  TttBoard b2("xx oo xo "); // board with spots already
  REQUIRE(b2.getSpace(0) == 'x');
  REQUIRE(b2.getSpace(4) == 'o');
}

TEST_CASE("responds to getters and setters", "[TttBoard]") {
  TttBoard b;

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

TEST_CASE("has a copy constructor and assignment operator", "[TttBoard]") {
  TttBoard b("xx ox xoo");
  TttBoard c(b);
  REQUIRE(b.getSpace(0) == c.getSpace(0));
  REQUIRE(b.getSpace(1) == c.getSpace(1));
  REQUIRE(b.getSpace(2) == c.getSpace(2));
  REQUIRE(b.getSpace(3) == c.getSpace(3));
  REQUIRE(b.getSpace(4) == c.getSpace(4));
  REQUIRE(b.getSpace(5) == c.getSpace(5));
  REQUIRE(b.getSpace(6) == c.getSpace(6));
  REQUIRE(b.getSpace(7) == c.getSpace(7));
  REQUIRE(b.getSpace(8) == c.getSpace(8));

  c.setSpace(4, ' ');
  REQUIRE(b.getSpace(4) != c.getSpace(4));

  TttBoard d = c;
  REQUIRE(c.getSpace(0) == d.getSpace(0));
  REQUIRE(c.getSpace(1) == d.getSpace(1));
  REQUIRE(c.getSpace(2) == d.getSpace(2));
  REQUIRE(c.getSpace(3) == d.getSpace(3));
  REQUIRE(c.getSpace(4) == d.getSpace(4));
  REQUIRE(c.getSpace(5) == d.getSpace(5));
  REQUIRE(c.getSpace(6) == d.getSpace(6));
  REQUIRE(c.getSpace(7) == d.getSpace(7));
  REQUIRE(c.getSpace(8) == d.getSpace(8));

  d.setSpace(8, 'x');
  REQUIRE(c.getSpace(8) != d.getSpace(8));
}

TEST_CASE("constructor initializes fields", "[TttGame]") {
  TttGame g;

  REQUIRE(g.getTurnNumber() == 0);
  REQUIRE(g.checkWinner() == false);
}

TEST_CASE("increments turn number", "[TttGame]") {
  TttGame g;

  REQUIRE(g.getTurnNumber() == 0);
  g.playMove(2);
  REQUIRE(g.getTurnNumber() == 1);
  g.playMove(3);
  REQUIRE(g.getTurnNumber() == 2);
}

TEST_CASE("copy constructor works", "[TttGame]") {
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

TEST_CASE("copy constructor works for derived class", "[AchiGame]") {
  AchiGame g;
  REQUIRE(g.getTurnNumber() == 0);
  REQUIRE(g.checkWinner() == false);

  g.playMove(8);
  REQUIRE(g.getTurnNumber() == 1);

  AchiGame h(g);
  REQUIRE(g.getTurnNumber() == 1);
  REQUIRE(h.getTurnNumber() == 1);
  REQUIRE(h.getBlankSpot() == g.getBlankSpot());

  g.playMove(3);
  REQUIRE(g.getTurnNumber() == 2);
  REQUIRE(h.getTurnNumber() == 1);

  h.playMove(2);
  h.playMove(1);
  h.playMove(6);
  REQUIRE(g.getTurnNumber() == 2);
  REQUIRE(h.getTurnNumber() == 4);
}

TEST_CASE("figures out the last move", "[TttGame]") {
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

TEST_CASE("figures out a couple moves", "[TttGame]") {
  TttGame g;
  g.playMove(2);
  g.playMove(0);
  g.playMove(3);
  g.playMove(7);
  g.playMove(6);
  g.playMove(8);

  REQUIRE(g.computeNextMove() == 4);
}

TEST_CASE("o wins too", "[TttGame]") {
  TttGame g;
  g.playMove(2);
  g.playMove(8);
  g.playMove(1);
  g.playMove(0);
  g.playMove(3);
  g.playMove(7);
  g.playMove(6);

  REQUIRE(g.computeNextMove() == 4);
}

TEST_CASE("o does not give up too soon", "[TttGame]") {
  TttGame g;
  g.playMove(1);
  g.playMove(7);
  g.playMove(5);
  g.playMove(6);
  g.playMove(8);

  REQUIRE(g.computeNextMove() == 2);
}

TEST_CASE("correctly detects the winner", "[TttGame]") {
  TttGame g;
  g.playMove(4); // x plays in the middle
  REQUIRE(g.board.getSpace(4) == 'x');
  g.playMove(5); // o plays on the side -- DUMB!
  g.playMove(1); // x plays on the top
  g.playMove(7); // o tries to block -- DUMB!
  g.playMove(0); // x sets himself up for victory
  g.playMove(8); // o can block but it's too late

  REQUIRE(g.checkWinner() == false);

  TttGame h(g); // save a copy of the incomplete game
  REQUIRE(h.checkWinner() == false);

  g.playMove(2); // x wins
  REQUIRE(g.board.getSpace(0) == 'x');
  REQUIRE(g.board.getSpace(1) == 'x');
  REQUIRE(g.board.getSpace(2) == 'x');
  REQUIRE(g.checkWinner() == true);

  REQUIRE(h.checkWinner() == false);
  h.playMove(3); // x deliberately screws up for test purposes
  REQUIRE(h.checkWinner() == false);
  h.playMove(2); // o exploits x's foolishness and seizes victory
  REQUIRE(h.board.getSpace(2) == 'o');
  REQUIRE(h.board.getSpace(5) == 'o');
  REQUIRE(h.board.getSpace(8) == 'o');
  REQUIRE(h.checkWinner() == true);
}

TEST_CASE("scores the winning board", "[TttGame]") {
  TttGame g;

  g.playMove(4);
  g.playMove(5);
  g.playMove(1);
  g.playMove(7);
  g.playMove(0);
  g.playMove(8);
  REQUIRE(g.score() == 0);
  g.playMove(2);
  REQUIRE(g.score() == 3);

  TttGame h;
  h.playMove(4);
  h.playMove(0);
  h.playMove(6);
  h.playMove(1);
  h.playMove(8);
  h.playMove(2);
  REQUIRE(h.score() == -4);
}

TEST_CASE("tells what achi possible moves exist", "[AchiGame]") {
  AchiGame a;

  a.playMove(2); // x
  REQUIRE(a.getBlankSpot() == -1);
  a.playMove(0); // o
  REQUIRE(a.getBlankSpot() == -1);
  a.playMove(3); // x
  REQUIRE(a.getBlankSpot() == -1);
  a.playMove(1); // o
  REQUIRE(a.getBlankSpot() == -1);
  a.playMove(8); // x
  REQUIRE(a.getBlankSpot() == -1);
  a.playMove(5); // o
  REQUIRE(a.getBlankSpot() == -1);
  a.playMove(6); // x
  REQUIRE(a.getBlankSpot() == -1);
  a.playMove(7); // o
  REQUIRE(a.board.getSpace(4) == ' ');
  REQUIRE(a.getBlankSpot() == 4);
  REQUIRE(a.checkWinner() == false);
  REQUIRE((a.isValidMove(0) | a.isValidMove(1) | a.isValidMove(4) | a.isValidMove(5) | a.isValidMove(7))  == false);
  REQUIRE((a.isValidMove(2) & a.isValidMove(3) & a.isValidMove(6) & a.isValidMove(8))  == true);

  a.playMove(3); // x
  REQUIRE(a.board.getSpace(3) == ' ');
  REQUIRE(a.getBlankSpot() == 3);
  REQUIRE(a.board.getSpace(4) == 'x');
  REQUIRE(a.checkWinner() == true);
}

TEST_CASE("picks a good move for o", "[AchiGame]") {
  AchiGame a;
  a.playMove(0); // x
  REQUIRE(a.tttFillMode() == true);
  a.playMove(1); // o
  REQUIRE(a.tttFillMode() == true);
  a.playMove(5); // x
  REQUIRE(a.tttFillMode() == true);
  a.playMove(2); // o
  REQUIRE(a.tttFillMode() == true);
  a.playMove(7); // x
  REQUIRE(a.tttFillMode() == true);
  a.playMove(8); // o
  REQUIRE(a.tttFillMode() == true);
  a.playMove(6); // x
  REQUIRE(a.tttFillMode() == true);
  a.playMove(3); // o
  REQUIRE(a.tttFillMode() == false);
  REQUIRE(a.getBlankSpot() == 4);
  REQUIRE(a.checkWinner() == false);
  REQUIRE(a.score() == 0);

  AchiGame b(a);
  b.playMove(7);
  REQUIRE(b.getBlankSpot() == 7);
  REQUIRE(b.checkWinner() == false);
  REQUIRE(a.tttFillMode() == false);
  b.playMove(8);
  REQUIRE(b.getBlankSpot() == 8);
  REQUIRE(b.checkWinner() == false);
  REQUIRE(a.tttFillMode() == false);
  b.playMove(5);
  REQUIRE(b.getBlankSpot() == 5);
  REQUIRE(b.checkWinner() == true);
  REQUIRE(b.score() == 989);
  REQUIRE(a.tttFillMode() == false);

  // X should play 7->4, forcing O 8->7, so X can play 5->8 to win
  REQUIRE(a.tttFillMode() == false);
  // REQUIRE(a.computeNextMove() == 7);
  a.playMove(7);
  REQUIRE(a.checkWinner() == false);

  /*
  // O's only valid move
  REQUIRE(a.computeNextMove() == 8);
  a.playMove(8);
  REQUIRE(a.checkWinner() == false);

  // X's winning move
  REQUIRE(a.computeNextMove() == 5);
  a.playMove(5);
  REQUIRE(a.checkWinner() == true);
  */
}

TEST_CASE("serializes the board", "[TttBoard]") {
  TttBoard b;
  REQUIRE(b.serialize() == 0);
}

