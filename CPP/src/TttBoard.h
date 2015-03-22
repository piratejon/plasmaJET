
#if ! defined (PLASMAJET_TTTBOARD_H)
#define PLASMAJET_TTTBOARD_H

class TttBoard {
  private:
    char board[9] = {' '};

  public:
    TttBoard(const char *);
    char at(const int);
};

#endif // PLASMAJET_TTTBOARD_H

