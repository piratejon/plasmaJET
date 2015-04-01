
#if ! defined(PLASMAJET_ACHIGAME_H)
#define PLASMAJET_ACHIGAME_H

#include "TttGame.h"

class AchiGame : public TttGame {
  private:
    int space; // simpler to set the free space in playmove

    void copy_from(const AchiGame &);

  public:
    AchiGame();
    AchiGame(const AchiGame &src);
    AchiGame & operator= (const AchiGame &);
    int computeNextMove();
    void playMove(int);
    int getBlankSpot() const;
    int computeBlankSpot() const;
};

#endif // PLASMAJET_ACHIGAME_H

