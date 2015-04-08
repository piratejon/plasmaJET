#!/usr/bin/python3

import unittest
import autoplay

LOAD_LIBRARY_ARGUMENT = ''

class TestAutoplay(unittest.TestCase):
  def setUp(self):
    self.game = autoplay.load_library(LOAD_LIBRARY_ARGUMENT)

  def test_play_a_game(self):
    self.assertIsNotNone(self.game)

  def test_a_whole_game(self):
    self.assertEqual(self.game.checkWinner(), 0);
    self.assertEqual(self.game.computeNextMove(), 0)
    self.game.playMove(0)
    self.assertEqual(self.game.checkWinner(), 0);
    self.assertEqual(self.game.computeNextMove(), 1)
    self.game.playMove(1)
    self.assertEqual(self.game.checkWinner(), 0);
    self.assertEqual(self.game.computeNextMove(), 3)
    self.game.playMove(3)
    self.assertEqual(self.game.checkWinner(), 0);
    self.assertEqual(self.game.computeNextMove(), 6)
    self.game.playMove(6)
    self.assertEqual(self.game.checkWinner(), 0);
    self.assertEqual(self.game.computeNextMove(), 4)
    self.game.playMove(4)
    self.assertEqual(self.game.checkWinner(), 0);
    self.assertEqual(self.game.computeNextMove(), 2)
    self.game.playMove(2)
    self.assertEqual(self.game.checkWinner(), 0);
    self.assertEqual(self.game.computeNextMove(), 5)
    self.game.playMove(5)
    self.assertEqual(self.game.checkWinner(), 1);

if __name__=='__main__':
  import sys
  print(sys.argv)
  LOAD_LIBRARY_ARGUMENT = sys.argv[1]
  sys.argv[1:] = sys.argv[2:]
  print(sys.argv)
  unittest.main()

