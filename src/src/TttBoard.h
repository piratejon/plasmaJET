
#if ! defined(PLASMAJET_TTTBOARD_H)
#define PLASMAJET_TTTBOARD_H

#include "TttSpace.h"

class TttBoard {
  private:
    TttSpace space[9];

  public:
    char getSpace(int);
    void setSpace(int, char);
};

#endif // PLASMAJET_TTTSPACE_H

