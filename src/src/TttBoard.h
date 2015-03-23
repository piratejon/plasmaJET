
#if ! defined(PLASMAJET_TTTBOARD_H)
#define PLASMAJET_TTTBOARD_H

#include "TttSpace.h"

class TttBoard {
  private:
    TttSpace space[9];

  public:
    TttBoard(); // empty board
    TttBoard(const char *); // preconfigured board
    TttBoard(TttBoard &); // copied board
    char getSpace(int);
    void setSpace(int, char);

    char decodeSpace(TttSpace);
    void encodeSpace(char);
};

#endif // PLASMAJET_TTTSPACE_H

