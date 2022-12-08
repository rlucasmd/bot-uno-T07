#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "cards.h"

Hand readHand(char *inputString)
{
  Hand myHand;
  myHand.tam = 7;
  myHand.cards = malloc(sizeof(Card) * 7);
  char *aux[7];
  char *parte;

  parte = strtok(inputString, "[ ");

  for (int i = 0; i < 7; i++)
  {
    aux[i] = malloc(sizeof(char) * (1 + strlen(parte)));
    strcpy(aux[i], parte);
    aux[i][strlen(parte)] = '\0';
    parte = strtok(NULL, " ");
  }

  for (int i = 0; i < 7; i++)
  {
    myHand.cards[i] = makeCard(aux[i]);
  }
  return myHand;
}

Card readTable(char *entrada)
{
  Card aux = makeCard(entrada);
  return aux;
}

void readPlayers(char *entrada, Game *game)
{
  int index = 0;

  char *part = strtok(entrada, " ");
  while (part)
  {
    strcpy(game->players[index], part);
    index++;
    part = strtok(NULL, " ");
  }
  game->players_count = index;
}