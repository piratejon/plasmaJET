
from ctypes import cdll

def printBoard(game):
  b = [chr(x) for x in [game.getSpace(i) for i in range(9)]]
  print('{}|{}|{}\n{}|{}|{}\n{}|{}|{}'.format(
        b[0], b[1], b[2],
        b[3], b[4], b[5],
        b[6], b[7], b[8]
        )
      )

def playTicTacToe(game):
  while (game.checkWinner() == False) & (game.getTurnNumber() < 9):
    move = game.computeNextMove()
    print("{}: {} will play {}".format(game.getTurnNumber(), 'o' if game.getTurnNumber() & 1 else 'x', move))
    game.playMove(move)
    printBoard(game)
  
  if game.checkWinner():
    print("{} wins!".format('o' if game.getTurnNumber() & 1 else 'o'))
  else:
    print("Game ended in a draw!")

def load_library(path):
  return cdll.LoadLibrary(path)

def main(args):
# only arg is full path to library
  full_path_to_library = args[0]
  game = load_library(full_path_to_library)
  if game is not None:
    playTicTacToe(game)
  else:
    print("unable to load library '{}' (must use full path)".format(full_path_to_library))

if __name__ == '__main__':
  import sys
  main(sys.argv[1:])

