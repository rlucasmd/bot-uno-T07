#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "debugger.h"
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
    game->players[index].buyedHand.tam = 0;
    index++;
    part = strtok(NULL, " ");
  }
  game->playersCount = index;
  game->botTurnIndex = -1;
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
  for (int i = 0; i < game->playersCount; i++)
  {
    if (strcmp(game->players[i].botId, game->gameAction->complement) == 0)
    {
      game->botTurnIndex = i;
    }
  }
}

void updateBuyedCard(Game *game)
{
  int botIndex = game->botTurnIndex;
  int qtdCards = game->players[botIndex].buyedHand.tam + 1;
  if (game->players[botIndex].buyedHand.tam == 0)
  {
    game->players[botIndex].buyedHand.cards = malloc(sizeof(Card) * qtdCards);
  }
  else
  {
    game->players[botIndex].buyedHand.cards = realloc(game->players[botIndex].buyedHand.cards, sizeof(Card) * qtdCards);
  }
  game->players[botIndex].buyedHand.cards[qtdCards - 1] = game->table;

  game->players[botIndex].buyedHand.tam += 1;
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
    game->players[game->botTurnIndex].cardsQuantity -= 1;
    int isDrawCard = convertCardToInt(makeCard(game->gameAction->complement));
    if (isDrawCard == JACK || isDrawCard == JOKER)
    {
      game->shouldBuySomeCard = 1;
    }
    if (isDrawCard == ACE || isDrawCard == JOKER)
    {
      strcpy(game->table.naipe, game->gameAction->secondComplement);
    }
    if (isDrawCard == QUEEN)
      game->flux *= -1;
  }

  if (action == BUY)
  {
    int quantityCardBuyed = atoi(game->gameAction->complement);
    game->players[game->botTurnIndex].cardsQuantity += quantityCardBuyed;
    if (strcmp(game->gameAction->complement, "1") == 0)
      updateBuyedCard(game);
    if (game->botTurnIndex >= 0)
    {
      // debug(game->players[game->botTurnIndex].botId);
    }
    game->shouldBuySomeCard = 0;
  }

  if (game->botTurnIndex >= 0)
  {
    // int atualBotIndex = game->botTurnIndex;
    int nextIndex = game->botTurnIndex + game->flux;
    int previousIndex = game->botTurnIndex - game->flux;
    if (nextIndex >= game->playersCount)
      nextIndex = 0;
    if (nextIndex < 0)
      nextIndex = game->playersCount - 1;
    if (previousIndex < 0)
      previousIndex = game->playersCount - 1;
    if (previousIndex >= game->playersCount)
      previousIndex = 0;

    game->nextBot = game->players[nextIndex];
    game->previousBot = game->players[previousIndex];
  }
}