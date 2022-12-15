#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "cards.h"
#include "hand.h"
#include "debugger.h"

int countNaipesOnHand(Hand myHand)
{
  int naipes[4] = {0};
  int num, value;
  for (int i = 0; i < myHand.tam; i++)
  {
    num = naipeToInt(myHand.cards[i].naipe);
    value = convertCardToInt(myHand.cards[i]);
    if(value != ACE)
      naipes[num] += 1;
  }
  
  int bigger = -1, pos = -1;
  for (int i = 0; i < 4; i++)
  {
    if (naipes[i] >= bigger)
    {
      bigger = naipes[i];
      pos = i;
    }
  }
  return pos;
}

int *cardsPositionCanIDiscard(Hand myHand, Game *game)
{
  int *cardsPosition = malloc(sizeof(int));
  int qtd = 0;
  cardsPosition[0] = 0;
  int isSpecial = 0;

  for (int i = 0; i < myHand.tam; i++)
  {
    isSpecial = convertCardToInt(myHand.cards[i]) == JOKER || convertCardToInt(myHand.cards[i]) == ACE;
    if (canDiscardThisCard(myHand.cards[i], game->table) || isSpecial == 1)
    {
      qtd += 1;
      cardsPosition = realloc(cardsPosition, (sizeof(int) * (qtd + 1)));
      cardsPosition[qtd] = i;
      cardsPosition[0] = qtd;
    }
  }

  return cardsPosition;
}

int checkIfBotDontHaveThisNaipe(Hand botHand, Card card)
{
  for (int i = 0; i < botHand.tam; i++)
  {
    if (strcmp(botHand.cards[i].naipe, card.naipe) == 0)
      return i;
  }

  return -1;
}

int isSpecial(Card card)
{
  int cardInt = convertCardToInt(card);
  if (cardInt == JOKER || cardInt == ACE || cardInt == JACK || cardInt == QUEEN)
    return 1;
  return 0;
}

int makeABetterChoice(Hand myHand, Game *game, int *cardPositions)
{
  int cardInt = 0;
  int isSpecialCard = 0;
  // se o próximo bot tiver menos carta que o nosso, tenta descartar um valete ou coringa
  if (game->nextBot.cardsQuantity < myHand.tam && game->nextBot.cardsQuantity < 4)
  {
    for (int i = 1; i <= cardPositions[0]; i++)
    {
      cardInt = convertCardToInt(myHand.cards[cardPositions[i]]);
      if (cardInt == JOKER || cardInt == JACK)
      {
        return cardPositions[i];
      }
    }
  }

  // verifica se há alguma carta rainha, se tiver e o bot anterior não tiver o naipe da rainha então jogamos ela para garantir que os outros bots comprem mais cartas
  for (int i = 1; i <= cardPositions[0]; i++)
  {
    cardInt = convertCardToInt(myHand.cards[cardPositions[i]]);
    if (cardInt == QUEEN && game->previousBot.cardsQuantity <= game->nextBot.cardsQuantity)
    {
      int queenCardPosition = cardPositions[i];

      if (checkIfBotDontHaveThisNaipe(game->previousBot.buyedHand, myHand.cards[queenCardPosition]) >= 0)
      {
        return queenCardPosition;
      }
    }
  }
  //verifica se há algum rei que possa ser jogado
  for (int i = 1; i <= cardPositions[0]; i++)
  {
    cardInt = convertCardToInt(myHand.cards[cardPositions[i]]);
    if(cardInt == KING){
      return cardPositions[i];
    }
  }
  //verifica se há alguma carta simples (carta sem ação) a ser jogada.
  for (int i = 1; i <= cardPositions[0]; i++)
  {
    isSpecialCard = isSpecial(myHand.cards[cardPositions[i]]);
    if (!isSpecialCard)
    {
      return cardPositions[i];
    }
  }

  // verifica se há alguma carta com o naipe ou o valor das possíveis cartas que o próximo bot não tenha
  for (int i = 1; i <= cardPositions[0]; i++)
  {
    if (hasTheCard(game->nextBot.buyedHand, myHand.cards[cardPositions[i]]) >= 0)
      return cardPositions[i];
  }

  return -1;
}

int makeAChoice(Hand myHand, Game *game)
{
  // Hand optionsToDiscard;
  int cardPosition = -1;
  int *cardsPosition = cardsPositionCanIDiscard(myHand, game);
  // debug("Cards to discard:");
  // printCardsCanIDiscard(myHand, cardsPosition);
  // printTable(game->table);
  // debug("Next bot:");
  // printBot(game->nextBot);
  // debug("Previous bot:");
  // printBot(game->previousBot);

  if (cardsPosition[0] == 1)
  {
    return cardsPosition[1];
  }

  cardPosition = makeABetterChoice(myHand, game, cardsPosition);

  if (cardPosition >= 0)
  {
    return cardPosition;
  }

  cardPosition = hasTheCard(myHand, game->table);
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