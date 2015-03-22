
#if ! defined(PLASMAJET_TTTGAME_H)
#define PLASMAJET_TTTGAME_H

#include "TttBoard.h"

class TttGame {
  private:
    int turnNumber; // 0-indexed; even=X, odd=O
    bool hasWinner; // set by playMove() when a winning condition occurs
    TttBoard board;

  public:
    int getNextMove();
    int getTurnNumber();

    void playMove(int);
    bool checkWinner();

    TttGame(); // start with empty board
    TttGame(TttGame &);

    int computeNextMove();
};

#endif // PLASMAJET_TTTGAME_H

