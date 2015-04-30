
#if ! defined(PLASMAJET_TTTGAME_H)
#define PLASMAJET_TTTGAME_H

#include "TttBoard.h"

class TttGame {
protected:
    int score_base;
    int turnNumber; // 0-indexed; even=X, odd=O
    bool hasWinner; // set by playMove() when a winning condition occurs

    bool check_for_win() const;
    void copy_from(const TttGame &);
    char playerByTurn() const;

    int alpha_beta(int, int, int) const;

public:
    TttBoard board;
    int getTurnNumber() const;
    void setTurnNumber(int);

    void playMove(int);
    bool checkWinner() const;

    TttGame(); // start with empty board
    TttGame(const TttGame &); // copy another game configuration
    TttGame & operator= (const TttGame &);

    int computeNextMove(int depth = 0) const;
    int score(int base) const;
    int score() const;
    bool isValidMove(int) const;
};

#endif // PLASMAJET_TTTGAME_H

