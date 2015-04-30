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
    game = play.load_game_object()
    game = play.store_new_board(['','','','','','','','',''], game, 0)
    self.assertEqual(chr(game.getSpace(0)), ' ')
    self.assertEqual(chr(game.getSpace(1)), ' ')
    self.assertEqual(chr(game.getSpace(2)), ' ')
    self.assertEqual(chr(game.getSpace(3)), ' ')
    self.assertEqual(chr(game.getSpace(4)), ' ')
    self.assertEqual(chr(game.getSpace(5)), ' ')
    self.assertEqual(chr(game.getSpace(6)), ' ')
    self.assertEqual(chr(game.getSpace(7)), ' ')
    self.assertEqual(chr(game.getSpace(8)), ' ')

    game = play.store_new_board([' ','x','o','x','x',' ','o','o','x'], game, 7)
    self.assertEqual(chr(game.getSpace(0)), ' ')
    self.assertEqual(chr(game.getSpace(1)), 'x')
    self.assertEqual(chr(game.getSpace(2)), 'o')
    self.assertEqual(chr(game.getSpace(3)), 'x')
    self.assertEqual(chr(game.getSpace(4)), 'x')
    self.assertEqual(chr(game.getSpace(5)), ' ')
    self.assertEqual(chr(game.getSpace(6)), 'o')
    self.assertEqual(chr(game.getSpace(7)), 'o')
    self.assertEqual(chr(game.getSpace(8)), 'x')

    game = play.store_new_board(['o','x','','x','','o','x','o',''], game, 6)
    self.assertEqual(chr(game.getSpace(0)), 'o')
    self.assertEqual(chr(game.getSpace(1)), 'x')
    self.assertEqual(chr(game.getSpace(2)), ' ')
    self.assertEqual(chr(game.getSpace(3)), 'x')
    self.assertEqual(chr(game.getSpace(4)), ' ')
    self.assertEqual(chr(game.getSpace(5)), 'o')
    self.assertEqual(chr(game.getSpace(6)), 'x')
    self.assertEqual(chr(game.getSpace(7)), 'o')
    self.assertEqual(chr(game.getSpace(8)), ' ')

    game = play.store_new_board(['o','x',' ','o','x','o','x','o','x'], game, 8)
    self.assertEqual(chr(game.getSpace(0)), 'o')
    self.assertEqual(chr(game.getSpace(1)), 'x')
    self.assertEqual(chr(game.getSpace(2)), ' ')
    self.assertEqual(chr(game.getSpace(3)), 'o')
    self.assertEqual(chr(game.getSpace(4)), 'x')
    self.assertEqual(chr(game.getSpace(5)), 'o')
    self.assertEqual(chr(game.getSpace(6)), 'x')
    self.assertEqual(chr(game.getSpace(7)), 'o')
    self.assertEqual(chr(game.getSpace(8)), 'x')

  def test_two_player_game(self):
    game_id = play.get_game_id()
    self.assertIsNotNone(game_id)
    self.assertEqual(play.get_status(game_id), "0")

    p1_id = play.get_player_id(game_id)
    self.assertIsNotNone(p1_id)
    self.assertEqual(play.get_status(game_id), "0")

    p2_id = play.get_player_id(game_id)
    self.assertIsNotNone(p2_id)

    self.assertNotEqual(p1_id, p2_id)
    # print('Game ID: {}; p1: {}; p2: {}'.format(game_id, p1_id, p2_id))

# game starts as x's turn
    self.assertEqual(play.get_status(game_id), "1")

# game starts with empty board
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['','','','','','','','',''])
    play.make_move(game_id, p1_id, 4)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['','','','','X','','','',''])
    play.make_move(game_id, p2_id, 0)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','','','','X','','','',''])
    play.make_move(game_id, p1_id, 1)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','','','',''])
    play.make_move(game_id, p2_id, 7)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','','','O',''])
    play.make_move(game_id, p1_id, 5)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','X','','O',''])
    play.make_move(game_id, p2_id, 3)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','X','','O',''])
    play.make_move(game_id, p1_id, 6)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','X','X','O',''])
    play.make_move(game_id, p2_id, 2)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','O','O','X','X','X','O',''])
    play.make_move(game_id, p1_id, 5)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','O','O','X','','X','O','X'])
    play.make_move(game_id, p2_id, 2)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','O','X','O','X'])
    play.make_move(game_id, p1_id, 1)
    self.assertEqual(play.get_status(game_id), "3")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','','X','O','X','O','X','O','X'])

  def test_autoplay_with_network(self):
    game_id = play.get_game_id()
    self.assertIsNotNone(game_id)
    self.assertEqual(play.get_status(game_id), "0")

    p1_id = play.get_player_id(game_id)
    self.assertIsNotNone(p1_id)
    self.assertEqual(play.get_status(game_id), "0")

    p2_id = play.get_player_id(game_id)
    self.assertIsNotNone(p2_id)

    self.assertNotEqual(p1_id, p2_id)
    # print('Game ID: {}; p1: {}; p2: {}'.format(game_id, p1_id, p2_id))

# game starts as x's turn
    self.assertEqual(play.get_status(game_id), "1")

    game = play.load_game_object()
    game.reset()

# game starts with empty board
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['','','','','','','','',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['','','','','X','','','',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','','','','X','','','',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','','','',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','','','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','X','','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','X','','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','X','X','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','O','O','X','X','X','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','O','O','X','','X','O','X'])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','O','X','O','X'])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "3")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','','X','O','X','O','X','O','X'])

  def test_autoplay_with_board_unpack(self):
    game_id = play.get_game_id()
    self.assertIsNotNone(game_id)
    self.assertEqual(play.get_status(game_id), "0")

    p1_id = play.get_player_id(game_id)
    self.assertIsNotNone(p1_id)
    self.assertEqual(play.get_status(game_id), "0")

    p2_id = play.get_player_id(game_id)
    self.assertIsNotNone(p2_id)

    self.assertNotEqual(p1_id, p2_id)
    # print('Game ID: {}; p1: {}; p2: {}'.format(game_id, p1_id, p2_id))

# game starts as x's turn
    self.assertEqual(play.get_status(game_id), "1")

    game = play.load_game_object()

# game starts with empty board
    board = ['','','','','','','','','']
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), board)
    self.assertEqual(game.getTurnNumber(), 0)
    game = play.store_new_board(board, game, 0)
    self.assertEqual(game.getTurnNumber(), 0)
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['','','','','X','','','',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','','','','X','','','',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','','','',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','','','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','','X','X','','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','X','','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','X','X','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','O','O','X','X','X','O',''])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "2")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','O','O','X','','X','O','X'])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p2_id, move)
    self.assertEqual(play.get_status(game_id), "1")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','X','','O','X','O','X','O','X'])
    move = game.computeNextMove()
    game.playMove(move)
    play.make_move(game_id, p1_id, move)
    self.assertEqual(play.get_status(game_id), "3")
    self.assertEqual(play.decode_grid_json(play.get_grid(game_id)), ['O','','X','O','X','O','X','O','X'])

if __name__=='__main__':
  if len(sys.argv) < 2:
    LOAD_LIBRARY_ARGUMENT = os.getcwd() + '/libplasmajetactoe.so'
  else:
    LOAD_LIBRARY_ARGUMENT = sys.argv[1]
  sys.argv[1:] = sys.argv[2:]
  unittest.main()

