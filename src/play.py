from urllib.request import urlopen
import urllib.parse
import urllib.request
import json
from ctypes import cdll

#sends request to the server with information
#all information sent to the server, including moves, will have a response of some sort
def send_to_server(url, values = None): 
  if (values != None):
    print(values)
    data = urllib.parse.urlencode(values)
    data = data.encode('utf-8')
    print(data)
    request = urllib.request.Request(url, data)
    print(request)
  else:
    request = url
  response = urllib.request.urlopen(request)
  response = response.read()
  return response

#gets the game id from the server
def get_game_id():
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=start&boardsize=3'
  game_id = send_to_server(url)
  return game_id

#creates a connection with the other player and returs your player id
def get_player_id(game_id):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=connect'
  values = {'gameid' : game_id}
  player_id = send_to_server(url, values)
  return player_id

#gets the status of the game
def get_status(game_id):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=status'
  values = {'gameid' : game_id}
  status = send_to_server(url, values)
  return status

#gets the game mode
def get_mode(game_id):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=mode'
  values = {'gameid' : game_id}
  mode = send_to_server(url, values)
  return mode

def make_move(game_id, player_id):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=move'
  print("here")
  position = input("Enter move 0-8: ")
  values = {'gameid' : game_id, 'playerid' : player_id, 'position' : position}
  return(send_to_server(url, values))

def get_grid(game_id):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=grid'
  values = {'gameid' : game_id}
  send_to_server(url, values)

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

def play_game(player, game_id, player_id):
  while get_status(game_id).decode() != "3" or get_status(game_id).decode() != "4":
    if get_status(game_id).decode() == player:
      if get_mode(game_id).decode() == "tictactoe":
        print("yolo")
        make_move(game_id, player_id)
      elif get_mode(game_id).decode() == "slide":
        print("slide TIME")

def play_tic_tac_toe(game):
  print("Welcome to PlasmaJetTacToe")
  url = ""
  player = get_player()
  game_id = "0"
  player_id = "0"
  if player == "1":
    game_id, player_id = player_a()
    play_game(player, game_id, player_id)
  elif player == "2":
    game_id, player_id = player_b()
    play_game(player, game_id, player_id)


def main(args):
  # The only argument is the full path to the library.  Later, arguments including the game type may appear.
  full_path_to_library = args[0]
  game = cdll.LoadLibrary(full_path_to_library)
  if game is not None:
    play_tic_tac_toe(game)
  else:
    print("unable to load library '{}' (must use full path)".format(full_path_to_library))

if __name__ == '__main__':
  import sys
  main(sys.argv[1:])