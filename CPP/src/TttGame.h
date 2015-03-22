
#if ! defined PLASMAJET_TTTGAME_H
#define PLASMAJET_TTTGAME_H

#include "TttBoard.h"

class TttGame {
  private:
    TttBoard * b;
    char player;
  public:
    TttGame(TttBoard &);
    TttGame(TttBoard &, const char);
    char winner() const;
    char turn() const;
};

#endif // PLASMAJET_TTTGAME_H

