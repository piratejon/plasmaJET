
#if ! defined(PLASMAJET_TTTWRAPPER_H)
#define PLASMAJET_TTTWRAPPER_H

#if defined(__cplusplus)
extern "C" {
#endif

int computeNextMove();
void playMove(int);
char getSpace(int);
bool checkWinner();
int getTurnNumber();
int setTurnNumber(int);

#if defined(__cplusplus)
}
#endif

#endif // PLASMAJET_TTTWRAPPER_H

