
#if ! defined(PLASMAJET_TTTGAME_H)
#define PLASMAJET_TTTGAME_H

class TttGame {
  private:
    int turnNumber; // 0-indexed; even=X, odd=O
    bool hasWinner; // set by playMove() when a winning condition occurs

  private:
    int getNextMove();
    int getTurnNumber();

    void playMove(int);
    bool checkWinner();
    TttGame(TttGame &);

    int computeNextMove();
}

#endif // PLASMAJET_TTTGAME_H

