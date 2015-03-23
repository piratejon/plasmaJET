
#if ! defined(PLASMAJET_TTTGAME_H)
#define PLASMAJET_TTTGAME_H

#include "TttBoard.h"

class TttGame {
  protected:
    int turnNumber; // 0-indexed; even=X, odd=O
    bool hasWinner; // set by playMove() when a winning condition occurs

    int minimax();
    bool check_for_win();

  public:
    TttBoard board;
    int getNextMove();
    int getTurnNumber();

    void playMove(int);
    bool checkWinner();

    TttGame(); // start with empty board
    TttGame(TttGame &); // copy another game configuration

    int computeNextMove();
};

#endif // PLASMAJET_TTTGAME_H

