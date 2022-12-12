#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

void debug(char *message) { fprintf(stderr, "%s\n", message); }

void printHand(Hand myHand)
{
  int last = myHand.tam - 1;
  fprintf(stderr, "[");
  for (int i = 0; i < last; i++)
  {
    fprintf(stderr, " %s%s,", myHand.cards[i].value, myHand.cards[i].naipe);
  }
  fprintf(stderr, " %s%s ]\n", myHand.cards[last].value, myHand.cards[last].naipe);
}

void printTable(Card table)
{
  char *tableCard = strcat(table.value, table.naipe);
  debug(tableCard);
}

void printCardsCanIDiscard(Hand myHand, int *positions)
{
  int last = positions[positions[0]];
  int j;
  fprintf(stderr, "[");
  for (int i = 1; i < positions[0]; i++)
  {
    j = positions[i];
    fprintf(stderr, " %s%s,", myHand.cards[j].value, myHand.cards[j].naipe);
  }
  fprintf(stderr, " %s%s ]\n", myHand.cards[last].value, myHand.cards[last].naipe);
}