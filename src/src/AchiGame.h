
#if ! defined(PLASMAJET_ABSTRACTTTTGAME_H)
#define PLASMAJET_ABSTRACTTTTGAME_H

#include "TTTGame.cpp"

class AchiGame : public TTTGame {
  public:
    int getNextMove();
};
#endif // PLASMAJET_ABSTRACTTTTGAME_H

