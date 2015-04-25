
#if ! defined(PLASMAJET_TTTBOARD_H)
#define PLASMAJET_TTTBOARD_H

#include <string>

#include "TttSpace.h"

class TttBoard {
private:
    TttSpace space[9];
    void copy(const TttBoard &);
    void setFromString(const char (&)[10]);

public:
    TttBoard(); // empty board
    TttBoard(int);
    TttBoard(const char (&)[10]); // preconfigured board
    TttBoard(TttBoard &); // copied board
    TttBoard& operator=(const TttBoard &); // another way to copy the board
    TttBoard& operator=(const char (&)[10]); // allow to set the board

    bool operator==(const char (&)[10]) const; // compare with a string!
    bool operator==(const TttBoard &) const;
    bool operator!=(const TttBoard &) const;
    char getSpace(int) const;
    void setSpace(int, char);

    char decodeSpace(TttSpace) const;
    TttSpace encodeSpace(char) const;

    int serialize() const;
    void deserialize(int);

    std::string toString() const;
};

#endif // PLASMAJET_TTTSPACE_H

