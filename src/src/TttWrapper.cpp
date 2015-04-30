
#include "TttWrapper.h"
#include "TttGame.h"

static TttGame tttGame;

int computeNextMove() {
    return tttGame.computeNextMove();
}

void playMove(int p) {
    tttGame.playMove(p);
}

char getSpace(int i) {
    return tttGame.board.getSpace(i);
}

bool checkWinner() {
    return tttGame.checkWinner();
}

int getTurnNumber() {
    return tttGame.getTurnNumber();
}

void setTurnNumber(int t) {
    tttGame.setTurnNumber(t);
}

