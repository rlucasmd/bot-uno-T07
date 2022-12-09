#include <stdio.h>
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