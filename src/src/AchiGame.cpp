
#include "AchiGame.h"

AchiGame::AchiGame() {
    this->score_base = 1000;
    this->space = -1;
}

bool
AchiGame::tttFillMode() const {
    return this->getTurnNumber() < 8;
}

void
AchiGame::updateBlankSpace() {
    if (this->tttFillMode()) {
        this->space = -1;
    } else {
        this->space = this->computeBlankSpot();
    }
}

void
AchiGame::playMove(int i) {
    if (this->tttFillMode()) {
        this->board.setSpace(i, this->playerByTurn());
    } else {
        this->board.setSpace(this->space, this->board.getSpace(i));
        this->board.setSpace(i, ' ');
    }
    this->turnNumber += 1;
    this->hasWinner = this->check_for_win();
    updateBlankSpace();

    // this->history.insert(this->bundle());
}

void
AchiGame::copy_from(const AchiGame & src) {
    TttGame::copy_from(src);
    this->space = src.space;
    this->score_base = src.score_base;
    this->history = src.history;
}

AchiGame::AchiGame(const AchiGame & src) : TttGame(src) {
    copy_from(src);
}

AchiGame &
AchiGame::operator= (const AchiGame & src) {
    copy_from(src);
    return *this;
}

int
AchiGame::getBlankSpot() const {
    return this->space;
}

int
AchiGame::computeBlankSpot() const {
    int blank = -1, i;
    for (i = 0; i < 9; i += 1) {
        if (this->board.getSpace(i) == ' ') blank = i;
    }
    return blank;
}

bool
AchiGame::isValidMove(int i) const {
    if (this->tttFillMode()) {
        return TttGame::isValidMove(i);
    } else {
        return board.getSpace(i) == this->playerByTurn() && this->achiAdjacent(i, this->getBlankSpot());
    }
}

bool
AchiGame::achiAdjacent(int src, int dst) const {
    static const bool achi_adjacent[9][9] = {
        { false,  true, false,  true,  true, false, false, false, false }, // 0 adjacent to 1,3,4
        { false,  true,  true, false,  true, false, false, false, false }, // 1 adjacent to 1,2,4
        { false,  true, false, false,  true,  true, false, false, false }, // 2 adjacent to 1,4,5
        { false,  true, false, false,  true, false,  true, false, false }, // 3 adjacent to 0,4,6
        {  true,  true,  true,  true,  true,  true,  true,  true,  true }, // 4 adjacent to everybody!
        { false, false,  true, false,  true, false, false, false,  true }, // 5 adjacent to 2,4,8
        { false, false, false,  true,  true, false, false,  true, false }, // 6 adjacent to 3,4,7
        { false, false, false, false,  true, false,  true, false,  true }, // 7 adjacent to 4,6,8
        { false, false, false, false,  true,  true, false,  true, false }, // 8 adjacent to 4,5,7
    };

    return src >= 0 && src < 9 && dst >= 0 && dst < 9 && achi_adjacent[src][dst];
}

bool
AchiGame::seenBefore(TttBoard &board, int turn) const {
    // checks if the board + whose turn it is has occurred before
    return this->history.end() != this->history.find(this->bundle(board, turn));
}

bool
AchiGame::seenBefore(int bundle) const {
    return this->history.end() != this->history.find(bundle);;
}

int
AchiGame::bundle(const TttBoard & b, int turn) const {
    int bundle = b.serialize();
    bundle |= ((turn & 1) << 18);
    return bundle;
}

int
AchiGame::bundle() const {
    return this->bundle(this->board, this->getTurnNumber() & 1);
}

int
AchiGame::alpha_beta(int depth, int alpha, int beta) const {
    int i, v, tmp_score;
    if (this->hasWinner) {
        v = this->score(this->score_base);
    } else {
        if (this->getTurnNumber() & 1) { // odd, minimize
            v = this->score_base;
            for (i = 0; i < 9; i += 1) {
                if (this->isValidMove(i)) {
                    AchiGame tmp(*this);
                    tmp.playMove(i);
                    if (!this->seenBefore(tmp.board, this->getTurnNumber() & 1)) {
                        tmp_score = tmp.alpha_beta(depth + 1, alpha, beta);
                        if (tmp_score < v) v = tmp_score;
                        if (v < beta) beta = v;
                        if (beta <= alpha) break;
                    }
                }
            }
        } else { // even, maximize
            v = 0 - this->score_base; // assume worst possible score for player
            for (i = 0; i < 9; i += 1) {
                if (this->isValidMove(i)) {
                    AchiGame tmp(*this);
                    tmp.playMove(i);
                    if (!this->seenBefore(tmp.board, this->getTurnNumber() & 1)) {
                        tmp_score = tmp.alpha_beta(depth + 1, alpha, beta);
                        if (tmp_score > v) v = tmp_score;
                        if (v > alpha) alpha = v;
                        if (beta <= alpha) break;
                    }
                }
            }
        }
    }

    return v;
}

int
AchiGame::computeNextMove(int depth) const {
    int i;
    int best_move = -1;
    int best_score = this->score(this->score_base);
    int tmp_score;

    if (!this->hasWinner) {
        // only loop scenario i have found has an out which is a one-move win
        // so check for wins first

        if (depth > 20) {
          if (this->getTurnNumber() & 1) return this->score_base;
          else return 0 - this->score_base;
        };

        for (i = 0; i < 9; i += 1) {
            if (this->isValidMove(i)) {
                AchiGame tmp(*this);
                tmp.playMove(i);

                // if (!this->seenBefore(tmp.bundle())) {

                    tmp_score = tmp.computeNextMove(depth + 1);
                    // tmp_score = tmp.alpha_beta(depth + 1, 0 - this->score_base, this->score_base);

                    if (best_move == -1) {
                        best_score = tmp_score;
                        best_move = i;
                    }

                    if (this->getTurnNumber() & 1) { // odd = O, minimize
                        if (tmp_score < best_score) {
                            best_score = tmp_score;
                            best_move = i;
                        }
                    } else { // even = X, maximize
                        if (tmp_score > best_score) {
                            best_score = tmp_score;
                            best_move = i;
                        }
                    }
                // }
            }
        }
    }

    return depth == 0 ? best_move : best_score;
}

