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
    self.assertIsNotNone(play.get_game(LOAD_LIBRARY_ARGUMENT))

  def test_build_query_string(self):
    p1 = play.get_server_query_string() + '?method=lol&controller=api'
    p2 = play.get_server_query_string() + '?controller=api&method=lol'
    t = play.create_server_query_string('lol')

    cond = (t == p1) ^ (t == p2)

    self.assertTrue(cond)

  def test_build_server_request(self):
    p1 = 'p1=v1&p2=v2&method=lol'
    p2 = 'p1=v1&method=lol&p2=v2'
    p3 = 'method=lol&p1=v1&p2=v2'
    p4 = 'method=lol&p2=v2&p1=v1'
    p5 = 'p2=v2&p1=v1&method=lol'
    p6 = 'p2=v2&method=lol&p1=v1'
    t = play.build_request_string('lol', {'p1':'v1', 'p2':'v2'})
    cond = sum(t == p for p in [p1, p2, p3, p4, p5, p6])
    self.assertEqual(cond, 1)

  def test_create_game(self):
    pass
#self.assertIsNotNone(play.getGameId())

if __name__=='__main__':
  if len(sys.argv) < 2:
    LOAD_LIBRARY_ARGUMENT = os.getcwd() + '/libplasmajetactoe.so'
  else:
    LOAD_LIBRARY_ARGUMENT = sys.argv[1]
  sys.argv[1:] = sys.argv[2:]
  unittest.main()

