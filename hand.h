#include "definitions.h"

Hand reallocateNCards(Hand, int);
Hand buyNCards(Hand, int);
Hand discard(Hand, int);
int canDiscardThisCard(Card, Card);
int canDiscardThisCardAC(Card, Card);
// int hasTheCard(Hand, Card);
Hand cardToDiscard(int, Hand, Game *);
