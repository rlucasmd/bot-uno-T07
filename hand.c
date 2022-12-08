#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "cards.h"
#include "strategy.h"

Hand reallocateNCards(Hand myHand, int n)
{
  int tam = myHand.tam + n;
  myHand.cards = realloc(myHand.cards, (sizeof(Card)) * (tam));
  return myHand;
}

Hand buyNCards(Hand myHand, int n)
{
  char read[5];
  int tam = myHand.tam;
  myHand = reallocateNCards(myHand, n);
  for (int i = tam; i < tam + n; i++)
  {
    scanf(" %[^\n]\n", read);
    myHand.cards[i] = makeCard(read);
    myHand.tam += 1;
  }
  return myHand;
}

Hand discard(Hand myHand, int position)
{
  int tam = myHand.tam;

  for (int j = position; j < tam - 1; j++)
  {
    myHand.cards[j] = myHand.cards[j + 1];
  }
  myHand = reallocateNCards(myHand, -1);
  myHand.tam -= 1;

  return myHand;
}

int canDiscardThisCard(Card table, Card handCard)
{
  int result = (strcmp(table.naipe, handCard.naipe) == 0) ||
               (strcmp(table.value, handCard.value) == 0);

  return result;
}

int hasTheCard(Hand myHand, Card table)
{
  for (int i = 0; i < myHand.tam; i++)
  {
    if (canDiscardThisCard(table, myHand.cards[i]))
    {
      return i;
    }
  }
  return -1;
}

Hand cardToDiscard(int position, Hand myHand, Game *game)
{
  int cardInt = convertCardToInt(myHand.cards[position]);
  int needsComplement = (cardInt == JOKER) || (cardInt == ACE);
  int mostNaipeOnHand = countNaipesOnHand(myHand);
  Card discardedCard = myHand.cards[position];

  if (needsComplement)
  {
    char *naipe = choseNaipe(mostNaipeOnHand);
    strcpy(game->table.naipe, naipe);

    printf("DISCARD %s%s %s\n", discardedCard.value, discardedCard.naipe, naipe);
    myHand = discard(myHand, position);
  }
  else
  {
    printf("DISCARD %s%s\n", discardedCard.value, discardedCard.naipe);
    myHand = discard(myHand, position);
  }

  return myHand;
}

