#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

char suits[4][4] = {{226, 153, 165, 0}, {226, 153, 166, 0}, {226, 153, 163, 0}, {226, 153, 160, 0}};

char *choseNaipe(int i)
{
  return suits[i];
}

int naipeToInt(char *naipe)
{
  if (strcmp(naipe, "♥") == 0)
    return HEART;
  if (strcmp(naipe, "♦") == 0)
    return DIAMONDS;
  if (strcmp(naipe, "♣") == 0)
    return CLUB;
  return SPADE;
}

Card makeCard(char *cardString)
{
  Card myCard;
  char *naipe;
  char *aux = (char *)malloc(sizeof(char) * (strlen(cardString) + 1));
  strcpy(aux, cardString);

  for (int i = 0; i < 4; i++)
  {
    naipe = strstr(aux, suits[i]);
    if (naipe != NULL)
    {
      strcpy(myCard.naipe, naipe);
      char *part;
      part = strtok(aux, suits[i]);
      strcpy(myCard.value, part);
      break;
    }
  }
  return myCard;
}

int convertCardToInt(Card card)
{
  int isV = strcmp(card.value, "V");
  if (isV == 0)
    return JACK;
  int isC = strcmp(card.value, "C");
  if (isC == 0)
    return JOKER;
  int isA = strcmp(card.value, "A");
  if (isA == 0)
    return ACE;
  return 0;
}