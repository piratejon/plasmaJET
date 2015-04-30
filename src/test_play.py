#!/usr/bin/python3

import unittest
import play
import os

LOAD_LIBRARY_ARGUMENT = ''

class TestPlay(unittest.TestCase):
  def setUp(self):
    pass
#self.game = autoplay.load_library(LOAD_LIBRARY_ARGUMENT)

  def test_we_are_alive(self):
    self.assertTrue(True)

  def test_init_library(self):
    self.assertIsNotNone(play.get_game(LOAD_LIBRARY_ARGUMENT))

  def test_create_server_game(self):
    self.assertEqual(play.create_server_query_string('lol'), play.get_server_query_string() + '?controller=api&method=lol')
#self.assertIsNotNone(play.create_server_game())

if __name__=='__main__':
  import sys
  if len(sys.argv) < 2:
    LOAD_LIBRARY_ARGUMENT = os.getcwd() + '/libplasmajetactoe.so'
  else:
    LOAD_LIBRARY_ARGUMENT = sys.argv[1]
  sys.argv[1:] = sys.argv[2:]
  unittest.main()

