#!/usr/bin/python3

import unittest
import play
import sys
import os

LOAD_LIBRARY_ARGUMENT = '' # overwritten in main

class TestPlay(unittest.TestCase):
  def setUp(self):
    pass

  def test_we_are_alive(self):
    self.assertTrue(True)

  def test_init_library(self):
    self.assertIsNotNone(play.load_game_object())
#self.assertIsNotNone(play.load_game_object(LOAD_LIBRARY_ARGUMENT))

  def test_build_query(self):
    qs = play.build_query('lol', {'p1': 'v1', 'p2': 'v2'})
    self.assertEqual(len(qs), 4)
    self.assertEqual(qs['method'], 'lol')
    self.assertEqual(qs['controller'], 'api')
    self.assertEqual(qs['p2'], 'v2')
    self.assertEqual(qs['p1'], 'v1')

  def test_create_game(self):
    self.assertIsNotNone(play.get_game_id())

  def test_get_grid(self):
    j = b'["","","","","","","","",""]'.decode('utf-8')
    self.assertEqual(play.decode_grid_json(j), ['','','','','','','','',''])

    j = b'["x","o","","x","","o","x","o",""]'.decode('utf-8')
    self.assertEqual(play.decode_grid_json(j), ['x','o','','x','','o','x','o',''])

  def test_store_board(self):
    game = play.store_new_board(['o','x','','x','','o','x','o',''])
    self.assertEqual(chr(game.getSpace(0)), 'o')
    self.assertEqual(chr(game.getSpace(1)), 'x')
    self.assertEqual(chr(game.getSpace(2)), ' ')
    self.assertEqual(chr(game.getSpace(3)), 'x')
    self.assertEqual(chr(game.getSpace(4)), ' ')
    self.assertEqual(chr(game.getSpace(5)), 'o')
    self.assertEqual(chr(game.getSpace(6)), 'x')
    self.assertEqual(chr(game.getSpace(7)), 'o')
    self.assertEqual(chr(game.getSpace(8)), ' ')

    game = play.store_new_board([' ','x','o','x','x',' ','o','o','x'])
    self.assertEqual(chr(game.getSpace(0)), ' ')
    self.assertEqual(chr(game.getSpace(1)), 'x')
    self.assertEqual(chr(game.getSpace(2)), 'o')
    self.assertEqual(chr(game.getSpace(3)), 'x')
    self.assertEqual(chr(game.getSpace(4)), 'x')
    self.assertEqual(chr(game.getSpace(5)), ' ')
    self.assertEqual(chr(game.getSpace(6)), 'o')
    self.assertEqual(chr(game.getSpace(7)), 'o')
    self.assertEqual(chr(game.getSpace(8)), 'x')

    game = play.store_new_board(['o','x',' ','o','x','o','x','o','x'])
    self.assertEqual(chr(game.getSpace(0)), 'o')
    self.assertEqual(chr(game.getSpace(1)), 'x')
    self.assertEqual(chr(game.getSpace(2)), ' ')
    self.assertEqual(chr(game.getSpace(3)), 'o')
    self.assertEqual(chr(game.getSpace(4)), 'x')
    self.assertEqual(chr(game.getSpace(5)), 'o')
    self.assertEqual(chr(game.getSpace(6)), 'x')
    self.assertEqual(chr(game.getSpace(7)), 'o')
    self.assertEqual(chr(game.getSpace(8)), 'x')

if __name__=='__main__':
  if len(sys.argv) < 2:
    LOAD_LIBRARY_ARGUMENT = os.getcwd() + '/libplasmajetactoe.so'
  else:
    LOAD_LIBRARY_ARGUMENT = sys.argv[1]
  sys.argv[1:] = sys.argv[2:]
  unittest.main()

