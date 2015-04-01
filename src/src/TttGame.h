
#if ! defined(PLASMAJET_TTTGAME_H)
#define PLASMAJET_TTTGAME_H

#include "TttBoard.h"

class TttGame {
  protected:
    int score_base = 10;
    int turnNumber; // 0-indexed; even=X, odd=O
    bool hasWinner; // set by playMove() when a winning condition occurs

    bool check_for_win() const;
    void copy_from(const TttGame &);

  public:
    TttBoard board;
    int getNextMove();
    int getTurnNumber();

    void playMove(int);
    bool checkWinner();

    TttGame(); // start with empty board
    TttGame(const TttGame &); // copy another game configuration
    TttGame & operator= (const TttGame &);

    int computeNextMove(int depth = 0);
    int score(int base) const;
    int score() const;
    bool isValidMove(int) const;
};

#endif // PLASMAJET_TTTGAME_H

