from urllib.request import urlopen
import urllib.parse
import urllib.request

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
  url = 'http://cs2.uco.edu/~gq011/tictactoe/?controller=api&method=mode'
  values = {'gameid' : gameId}
  mode = sendToServer(url, values)
  return mode

def makeMove(gameId, playerId):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/?controller=api&method=move'
  position = getMove()
  values = {'gameid' : gameId, 'playerid' : playerId, 'position' : position}
  sendToServer(url, values)

def getGrid(gameId):
  url = 'http://cs2.uco.edu/~gq011/tictactoe/?controller=api&method=grid'
  values = {'gameid' : gameId}
  sendToServer(url, values)

gameId = getGameId #getGameId()
playerId = getPlayerId(gameId)
getStatus(gameId)
mode = getMode(gameId)
print(gameId)
print(playerId)
print(getGrid(gameId))
#makeMove(gameId, playerId)
print(getGrid(gameId))
print(mode)
#playGame()
print('done')