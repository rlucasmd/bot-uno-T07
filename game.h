#include "definitions.h"

Hand readHand(char *);
Card readTable(char *);
void readPlayers(char *, Game *);
void readAction(Game *);
int hasSecondComplement(Card);