
#if ! defined PLASMAJET_TTTGAME_H
#define PLASMAJET_TTTGAME_H

#include "TttBoard.h"

class TttGame {
  private:
    TttBoard * b;
  public:
    TttGame(TttBoard &);
    char winner();
};

#endif // PLASMAJET_TTTGAME_H

