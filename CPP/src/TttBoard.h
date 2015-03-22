
#if ! defined (PLASMAJET_TTTBOARD_H)
#define PLASMAJET_TTTBOARD_H

class TttBoard {
  private:
    char board[9] = {' '};

  public:
    TttBoard(const char *);
    char at(const int) const;
    void set(const int, const char);
};

#endif // PLASMAJET_TTTBOARD_H

