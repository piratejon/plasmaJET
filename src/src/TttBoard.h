
#if ! defined(PLASMAJET_TTTBOARD_H)
#define PLASMAJET_TTTBOARD_H

#include "TttSpace.h"

class TttBoard {
  private:
    TttSpace space[9];
    void copy(const TttBoard &);

  public:
    TttBoard(); // empty board
    TttBoard(const char *); // preconfigured board
    TttBoard(TttBoard &); // copied board
    TttBoard& operator=(const TttBoard&); // another way to copy the board
    char getSpace(int);
    void setSpace(int, char);

    char decodeSpace(TttSpace);
    TttSpace encodeSpace(char);
};

#endif // PLASMAJET_TTTSPACE_H

