
#if ! defined(PLASMAJET_ACHIGAME_H)
#define PLASMAJET_ACHIGAME_H

#include "TttGame.h"

class AchiGame : public TttGame {
  private:
    int space; // simpler to set the free space in playmove

    void copy_from(const AchiGame &);
    void updateBlankSpace();

    bool achiAdjacent(int, int) const;

  public:
    AchiGame();
    AchiGame(const AchiGame &src);
    AchiGame & operator= (const AchiGame &);
    int computeNextMove(int depth = 0) const;
    void playMove(int);
    int getBlankSpot() const;
    int computeBlankSpot() const;
    bool tttFillMode() const;
    bool isValidMove(int) const;
};

#endif // PLASMAJET_ACHIGAME_H

