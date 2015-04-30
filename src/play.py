from urllib.request import urlopen
import urllib.parse
import urllib.request
import json

import autoplay

SERVER_PATH = 'http://cs2.uco.edu/~gq011/tictactoe/server/'

def get_game(library_path):
  return autoplay.load_library(library_path)

def get_server_query_string():
  return SERVER_PATH

def create_server_query_string(method):
  return SERVER_PATH + '?' + urllib.parse.urlencode({'controller': 'api', 'method': method})

def build_request_string(method, params):
  params['method'] = method
  return SERVER_PATH + '?' + urllib.parse.urlencode(params)

def getMove():
	return 5

#sends request to the server with information
#all information sent to the server, including moves, will have a response of some sort
def sendToServer(url, values = None): 
  if (values != None):
    data = urllib.parse.urlencode(values)
    data = data.encode('utf-8')
    request = urllib.request.Request(url, data)
  else:
    request = url

  response = urllib.request.urlopen(request)
  response = response.read()
  return response


def playerBGameId():
  print("Enter Game ID")
  gameID = input(">")
  return gameID

#gets the game id from the server
def getGameId():
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=start&boardsize=3'
  gameId = sendToServer(url)
  return gameId

#creates a connection with the other player and returs your player id
def getPlayerId(gameId):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=connect'
  values = {'gameid' : gameId}
  playerId = sendToServer(url, values)
  return playerId

#gets the status of the game
def getStatus(gameId):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=status'
  values = {'gameid' : gameId}
  status = sendToServer(url, values)
  return status

#gets the game mode
def getMode(gameId):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=mode'
  values = {'gameid' : gameId}
  mode = sendToServer(url, values)
  return mode

def makeMove(gameId, playerId):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=move'
  position = input("Enter move 0-9: ")
  values = {'gameid' : gameId, 'playerid' : playerId, 'position' : position}
  return(sendToServer(url, values))

def getGrid(gameId):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/server/?controller=api&method=grid'
  values = {'gameid' : gameId}
  sendToServer(url, values)

if __name__ == '__main__':
  
  print("Welcome to PlasmaJetTacToe")
  print("Are you Player 1 (a) or Player 2 (b)?")
  
  player = 'c'
  while player != 'a' or player != 'b':  
    player = input(">")
    if player == 'a':
      print("hello player 1")
      gameId = getGameId()
      playerId = getPlayerId(gameId)
      print(gameId)
      print("Has the opponent got their player ID (y/n)?")
      opponent = False
      opponentId = input(">")
      if opponentId == 'y':
        opponent == True
        break
      break
    elif player == 'b':
      print("hello player 2")
      gameId = playerBGameId()
      opponent = False
      while opponent == False: 
        print("Has the opponent got their player ID (y/n)?")
        opponentId = input(">")
        if opponentId == 'y':
          opponent == True
          break
      playerId = getPlayerId(gameId)
      break
    else:
      print("Enter a or b")
  
  while getStatus(gameId).decode() != '3' or getStatus(gameId).decode() != '4':
    print(getStatus(gameId).decode())
    if player == 'a':
      if getStatus(gameId).decode() == '1':
        print("here")
        print(makeMove(gameId, playerId))
        grid = getGrid(gameId)
        print(json.dumps(grid))
    elif player == 'b':
      if getStatus(gameId).decode() == '2':
        print(makeMove(gameId, playerId))
        grid = getGrid(gameId)
        print(json.dumps(grid))
    if getStatus(gameId).decode() == '3' or getStatus(gameId).decode() == '4':
      break

  print(getStatus(gameId))





