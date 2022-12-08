#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "cards.h"
#include "hand.h"

int countNaipesOnHand(Hand myHand)
{
  int naipes[4] = {0};
  int num;
  for (int i = 0; i < myHand.tam; i++)
  {
    num = naipeToInt(myHand.cards[i].naipe);
    naipes[num] += 1;
  }
  int bigger = -1, pos = -1;
  for (int i = 0; i < 4; i++)
  {
    if (bigger < naipes[i])
    {
      bigger = naipes[i];
      pos = i;
    }
  }
  return pos;
}

int makeAChoice(Hand myHand, Game *game)
{
  int cardPosition = hasTheCard(myHand, game->table);
  if (cardPosition >= 0)
    return cardPosition;

  int cardNaipe = 0;

  for (int i = 0; i < myHand.tam; i++)
  {
    cardNaipe = convertCardToInt(myHand.cards[i]);
    if ((cardNaipe == JOKER || cardNaipe == ACE))
    {
      return i;
    }
  }
  return -1;
}