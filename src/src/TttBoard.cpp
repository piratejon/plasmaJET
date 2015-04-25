#include <sstream>
#include <string>

#include "TttBoard.h"

TttBoard::TttBoard() {
    int i;
    for(i = 0; i < 9; i++) {
        this->space[i] = Blank;
    }
}

void
TttBoard::setFromString(const char (&s)[10]) {
    int i;
    for(i = 0; i < 9; i++) {
        this->space[i] = encodeSpace(s[i]);
    }
}

//preconfigured board
TttBoard::TttBoard(const char (&src)[10]) {
    this->setFromString(src);
}

//Copied board
TttBoard::TttBoard(TttBoard &src) {
    int i;
    for(i = 0; i < 9; i++) {
        this->space[i] = src.space[i];
    }
}

TttBoard &
TttBoard::operator=(const TttBoard &src) {
    int i;
    for(i = 0; i < 9; i++) {
        this->space[i] = src.space[i];
    }
    return *this;
}

char
TttBoard::getSpace(int space) const {
    return decodeSpace(this->space[space]);
}

void
TttBoard::setSpace(int space, char player) {

    switch(player) {
    case 'x' :
        this->space[space] = X;
        break;
    case 'o' :
        this->space[space] = O;
        break;
    case ' ' :
        this->space[space] = Blank;
        break;
    }

    return;
}

char
TttBoard::decodeSpace(TttSpace space) const {
    char value;
    switch(space) {
    case X :
        value = 'x';
        break;
    case O :
        value = 'o';
        break;
    case Blank :
        value = ' ';
        break;
    }

    return value;
}

TttSpace
TttBoard::encodeSpace(char space) const {
    TttSpace tttspace;
    switch(space) {
    case 'x' :
        tttspace = X;
        break;
    case 'o' :
        tttspace = O;
        break;
    case ' ' :
        tttspace = Blank;
        break;
    }
    return tttspace;
}

TttBoard &
TttBoard::operator= (const char (&s)[10]) {
    this->setFromString(s);
    return *this;
}

int
TttBoard::serialize() const {
    int s = 0, i;

    for (i = 0; i < 9; i += 1) {
        s <<= 2;
        switch(this->space[i]) {
        case X:
            s |= 3;
            break;
        case O:
            s |= 1;
            break;
        case Blank:
            break; // nothing!
        }
    }

    return s;
}

bool
TttBoard::operator== (const char (&s)[10]) const {
    int i;
    for (i = 0; i < 9; i += 1) {
        char c = this->decodeSpace(this->space[i]);
        if (c != s[i]) return false;
    }
    return true;
}

void
TttBoard::deserialize (int s) {
    int i;
    for (i = 8; i >= 0; i -= 1, s >>= 2) {
        if ((s & 3) == 3) this->space[i] = X;
        else if ((s & 1) == 1) this->space[i] = O;
        else this->space[i] = Blank;
    }
}

bool
TttBoard::operator== (const TttBoard & t) const {
    int i;
    for (i = 0; i < 9; i += 1) {
        if (this->space[i] != t.space[i]) {
            return false;
        }
    }
    return true;
}

bool
TttBoard::operator!= (const TttBoard & t) const {
    return !((*this) == t);
}

TttBoard::TttBoard (int s) {
    this->deserialize(s);
}

std::string
TttBoard::toString() const {
    std::stringstream ss;
    ss << this->getSpace(0) << this->getSpace(1) << this->getSpace(2) << "\\n"
        << this->getSpace(3) << this->getSpace(4) << this->getSpace(5) << "\\n"
        << this->getSpace(6) << this->getSpace(7) << this->getSpace(8);
    return ss.str();
}

