#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

char suits[4][4] = {{-30, -103, -91, 0}, {-30, -103, -90, 0}, {-30, -103, -93, 0}, {-30, -103, -96, 0}};

char *choseNaipe(int i)
{
  return suits[i];
}

int naipeToInt(char *naipe)
{
  if (strcmp(naipe, suits[HEART]) == 0)
    return HEART;
  if (strcmp(naipe, suits[DIAMONDS]) == 0)
    return DIAMONDS;
  if (strcmp(naipe, suits[CLUB]) == 0)
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
  int isD = strcmp(card.value, "D");
  if (isD == 0)
    return QUEEN;
  int isK = strcmp(card.value, "R");
  if (isK == 0)
    return KING;
  return 0;
}