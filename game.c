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
    game->players[index].cardsQuantity = 7;
    strcpy(game->players[index].botId, part);
    index++;
    part = strtok(NULL, " ");
  }
  game->playersCount = index;
}

int hasSecondComplement(Card table)
{
  int a = strcmp(table.value, "A");
  int c = strcmp(table.value, "C");
  if (a == 0 || c == 0)
    return 1;
  return 0;
}

void readAction(Game *game)
{
  scanf("%s %s", game->gameAction->action, game->gameAction->complement);
  if (strcmp(game->gameAction->action, "DISCARD") == 0)
  {
    game->table = makeCard(game->gameAction->complement);
    if (hasSecondComplement(game->table))
    {
      scanf("%s\n", game->gameAction->secondComplement);
    }
  }
}

int convertActionToInt(GameAction gameAction)
{
  if (strcmp(gameAction.action, "DISCARD") == 0)
    return DISCARD;
  if (strcmp(gameAction.action, "BUY") == 0)
    return BUY;
  if (strcmp(gameAction.action, "TURN") == 0)
    return TURN;

  return TURN;
}

void updateOtherBotActions(Game *game)
{
  int isMyBot = strcmp(game->gameAction->complement, game->myId);
  if (isMyBot != 0)
  {
  }
}

void updateGame(Game *game)
{
  int action = convertActionToInt(*((*game).gameAction));

  if (action == TURN)
  {
    updateOtherBotActions(game);
  }

  if (action == DISCARD)
  {
    int isDrawCard = convertCardToInt(makeCard(game->gameAction->complement));
    if (isDrawCard == JACK || isDrawCard == JOKER)
    {
      game->shouldBuySomeCard = 1;
    }
    if (isDrawCard == ACE || isDrawCard == JOKER)
    {
      strcpy(game->table.naipe, game->gameAction->secondComplement);
    }
  }

  if (action == BUY)
  {
    game->shouldBuySomeCard = 0;
  }
}