#include "definitions.h"

Hand reallocateNCards(Hand, int);
Hand buyNCards(Hand, int);
Hand discard(Hand, int);
int canDiscardThisCard(Card, Card);
int hasTheCard(Hand, Card);
Hand cardToDiscard(int, Hand, Game *);
int isTheSameCard(Card, Card);
