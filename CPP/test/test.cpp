
#include <gtest/gtest.h>

#include "TttBoard.h"
#include "TttGame.h"

namespace {
  class TttTest : public ::testing::Test {
  };
}

TEST_F(TttTest, BoardFromString) {
  TttBoard t = TttBoard("xx oo xox");
  ASSERT_EQ(t.at(0), 'x');
  ASSERT_EQ(t.at(1), 'x');
  ASSERT_EQ(t.at(2), ' ');

  t.from_string("xoxoxoxox");
  ASSERT_EQ(t.at(0), 'x');
  ASSERT_EQ(t.at(1), 'o');
  ASSERT_EQ(t.at(4), 'x');
}

TEST_F(TttTest, BoardIsWinning) {
  TttBoard t = TttBoard("xx oo xox");
  TttGame r = TttGame(t);
  ASSERT_EQ(r.winner(), ' ');
  t.set(2, 'x');
  ASSERT_EQ(r.winner(), 'x');
}

TEST_F(TttTest, BoardSetters) {
  TttBoard t = TttBoard("xx oo xox");
  ASSERT_EQ(t.at(2), ' ');
  t.set(2, 'x');
  ASSERT_EQ(t.at(2), 'x');
  t.set(2, 'o');
  ASSERT_EQ(t.at(2), 'o');
}

TEST_F(TttTest, TrackTurn) {
  TttBoard t = TttBoard("xx oo xox");
  TttGame g = TttGame(t, 'o');
  ASSERT_EQ(g.turn(), 'o');
}

TEST_F(TttTest, ComputeNextMove) {
  TttBoard t = TttBoard("xx oo xox");
  TttGame g = TttGame(t, 'o');
  ASSERT_EQ(g.computeNextMove(), 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

