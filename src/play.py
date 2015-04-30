from urllib.request import urlopen
import urllib.parse
import urllib.request
import json
from ctypes import cdll

API_URL = 'http://cs2.uco.edu/~gq011/tictactoe/server/'

def build_query(method, values = {}):
  values['controller'] = 'api'
  values['method'] = method
  return values

def build_query_string(query):
  return urllib.parse.urlencode(query).encode('utf-8')

def load_game_object(library_path):
  return cdll.LoadLibrary(library_path)

#sends request to the server with information
#all information sent to the server, including moves, will have a response of some sort
def send_to_server(method, values = {}):
  data = build_query_string(build_query(method, values))
  request = urllib.request.Request(API_URL, data)
  response = urllib.request.urlopen(request)
  response = response.read()
  return response.decode('utf-8')

#gets the game id from the server
def get_game_id():
  return send_to_server('start', {'boardsize': 3})

#creates a connection with the other player and returs your player id
def get_player_id(game_id):
  return send_to_server('connect', {'gameid': game_id})

#gets the status of the game
def get_status(game_id):
  return send_to_server('status', {'gameid': game_id})

#gets the game mode
def get_mode(game_id):
  return send_to_server('mode', {'gameid': game_id})

def make_move(game_id, player_id, position):
  return send_to_server('move', {'gameid' : game_id, 'playerid' : player_id, 'position' : position})

def get_grid(game_id):
  return send_to_server('grid', {'gameid' : game_id})

def decode_grid_json(grid):
  return json.JSONDecoder().decode(grid)

def get_player():
  print("Are you Player 1 or Player 2?")

  player = "0"
  while player != "1" and player != "2":  
    player = input(">")
    if player == "1":
      print("Welcome Player 1, here's to an easy win!!!")
    elif player == "2":
      print("Welcome Player 2. Our implementation is better than their is, so you'll still win.")
    else:
      print("What? Try that again.")

  return player

def player_a():
  # Player A, being the first player connecting to the server, gets both the game ID and the first player ID.
  game_id = get_game_id()
  player_id = get_player_id(game_id)

  print(game_id)
  print("Tell that scrappy dude across the table what the game ID is so they can connect their measly system to yours.")
  print("Has the opponent got their player ID (y/n)?")
  opponent = False
  while opponent == False: 
    opponent_received_id = input(">")
    if opponent_received_id == "y":
      opponent = True
      print("Well, good for them.")
    elif opponent_received_id == "n":
      print("They need to get their act together, huh?")
      print("Have they received it yet?")
    else:
      print("What? Try that again.")

  return game_id, player_id

def player_b():
  # Player B, being the second player connecting to the server, has to input the game id to get their player ID.
  
  print("Has that idiot given you a game ID yet?")
  game_initialized = False
  while game_initialized == False:
    opponent_received_game_id = input(">")
    if opponent_received_game_id == "y":
      game_initialized = True
      print("Well, good for them.")
    elif opponent_received_game_id == "n":
      print("Tell them to hurry up. It's late and I want to go home.")
      print("Ask them until they say yes.")
    else:
      print("I don't even know what you're trying to say.")

  print("Well, what is it?")
  game_id = input(">")
  print(game_id)
  print("You sure that's it?")
  sure = False
  while sure != True:
    verification = input(">")
    if verification == "y":
      sure = True
    elif verification == "n":
      sure = False
    else:
      print("What?")

  print("What about their player ID? Have they got that?")
  player_one_initialized = False
  while player_one_initialized == False:
    opponent_received_player_id = input(">")
    if opponent_received_player_id == "y":
      player_one_initialized = True
      print("Took way too long.")
    elif opponent_received_player_id == "n":
      print("I bet they don't want to go home and be alone in their filth. That's why they are stalling.")
      print("Bug them until they do.")
    else:
      print("What?")

  player_id = get_player_id(game_id)
  print(player_id)

  return game_id, player_id

def play_game(player, game_id, player_id, game):
  while get_status(game_id).decode() != "3" and get_status(game_id).decode() != "4":
    if get_status(game_id).decode() == player:
      if get_mode(game_id).decode() == "tictactoe":
        position = game.computeNextMove()
        print("{}: {} will play {}".format(game.getTurnNumber(), 'o' if game.getTurnNumber() & 1 else 'x', position))
        make_move(game_id, player_id, position)
      elif get_mode(game_id).decode() == "slide":
        print("It's achi time bb!!!!!!!")
        position = game.computeNextMove()
        print("{}: {} will play {}".format(game.getTurnNumber(), 'o' if game.getTurnNumber() & 1 else 'x', position))
        make_move(game_id, player_id, position)
    game = load_game_object(full_path_to_library)    
  print("GAME OVER")
  if get_status(game_id).decode() == "3":
    print("Player 1 is the winner")
  elif get_status(game_id).decode() == "4":
    print("Player 2 is the winner")   

def play_tic_tac_toe(game):
  print("Welcome to PlasmaJetTacToe")
  url = ""
  player = get_player()
  game_id = "0"
  player_id = "0"
  if player == "1":
    game_id, player_id = player_a()
    play_game(player, game_id, player_id, game)
  elif player == "2":
    game_id, player_id = player_b()
    play_game(player, game_id, player_id, game)


def main(args):
  # The only argument is the full path to the library.  Later, arguments including the game type may appear.
  full_path_to_library = args[0]
  game = load_game_object(full_path_to_library)
  if game is not None:
    play_tic_tac_toe(game)
  else:
    print("unable to load library '{}' (must use full path)".format(full_path_to_library))

if __name__ == '__main__':
  import sys
  main(sys.argv[1:])

