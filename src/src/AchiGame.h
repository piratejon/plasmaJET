
#if ! defined(PLASMAJET_ACHIGAME_H)
#define PLASMAJET_ACHIGAME_H

#include "TttGame.h"

class AchiGame : public TttGame {
  public:
    int computeNextMove();
    void playMove();
};

#endif // PLASMAJET_ACHIGAME_H

