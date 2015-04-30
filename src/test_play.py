#!/usr/bin/python3

import unittest
import play
import sys
import os

LOAD_LIBRARY_ARGUMENT = ''

class TestPlay(unittest.TestCase):
  def setUp(self):
    pass
#self.game = autoplay.load_library(LOAD_LIBRARY_ARGUMENT)

  def test_we_are_alive(self):
    self.assertTrue(True)

  def test_init_library(self):
    self.assertIsNotNone(play.load_game_object(LOAD_LIBRARY_ARGUMENT))

  def test_build_query(self):
    qs = play.build_query('lol', {'p1': 'v1', 'p2': 'v2'})
    self.assertEqual(len(qs), 4)
    self.assertEqual(qs['method'], 'lol')
    self.assertEqual(qs['controller'], 'api')
    self.assertEqual(qs['p2'], 'v2')
    self.assertEqual(qs['p1'], 'v1')

  def test_create_game(self):
    self.assertIsNotNone(play.get_game_id())

if __name__=='__main__':
  if len(sys.argv) < 2:
    LOAD_LIBRARY_ARGUMENT = os.getcwd() + '/libplasmajetactoe.so'
  else:
    LOAD_LIBRARY_ARGUMENT = sys.argv[1]
  sys.argv[1:] = sys.argv[2:]
  unittest.main()

