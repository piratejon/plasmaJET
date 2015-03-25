
#if ! defined(PLASMAJET_TTTGAME_H)
#define PLASMAJET_TTTGAME_H

#include "TttBoard.h"

class TttGame {
  protected:
    int turnNumber; // 0-indexed; even=X, odd=O
    bool hasWinner; // set by playMove() when a winning condition occurs

    bool check_for_win();

  public:
    TttBoard board;
    int getNextMove();
    int getTurnNumber();

    void playMove(int);
    bool checkWinner();

    TttGame(); // start with empty board
    TttGame(TttGame &); // copy another game configuration

    int computeNextMove(int depth = 0);
    int score();
};

#endif // PLASMAJET_TTTGAME_H

