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

//Verifica as posições das cartas da mão que podem ser descartadas
int *cardsPositionCanIDiscard(Hand myHand, Game *game)
{
  int *cardsPosition = malloc(sizeof(int));
  int qtd = 0;
  cardsPosition[0] = 0;

  //Verifica as posições das cartas da mão que podem ser descartadas (E que nao são ACE ou JOKER)
  for (int i = 0; i < myHand.tam; i++)
  {
    if (canDiscardThisCard(game->table, myHand.cards[i]))
    {
      qtd += 1;
      cardsPosition = realloc(cardsPosition, (sizeof(int) * (qtd + 1)));
      cardsPosition[qtd] = i;
      cardsPosition[0] = qtd;
    }
  }

  //Verifica as posições das cartas da mão que são ACE ou JOKER
  for (int i = 0; i < myHand.tam; i++)
  {
    if (canDiscardThisCardAC(game->table, myHand.cards[i]))
    {
      qtd += 1;
      cardsPosition = realloc(cardsPosition, (sizeof(int) * (qtd + 1)));
      cardsPosition[qtd] = i;
      cardsPosition[0] = qtd;
    }
  }

  return cardsPosition;
}

//Escolhe uma carta para descartar
int makeAChoice(Hand myHand, Game *game)
{
  int *cardsPosition = cardsPositionCanIDiscard(myHand, game);

  if (cardsPosition[0] == 0) return -1;
  
  int mostNaipeOnHand = countNaipesOnHand(myHand);
  //Tenta descartar primeiro uma carta com o naipe de maior frequência na mão(que nao seja ACE ou JOKER)
  for(int i = 1; i <= cardsPosition[0]; i++)
  {
    if((strcmp(myHand.cards[cardsPosition[i]].value, "A") != 0) && 
       (strcmp(myHand.cards[cardsPosition[i]].value, "C") != 0) && 
       (naipeToInt(myHand.cards[cardsPosition[i]].naipe) == mostNaipeOnHand))
    {
      return cardsPosition[i];
    }
  }

  //Verficia se possui descarte possível que nao seja JOKER ou ACE
  for(int i = 1; i <= cardsPosition[0]; i++)
  {
    if((strcmp(myHand.cards[cardsPosition[i]].value, "A") != 0) && 
       (strcmp(myHand.cards[cardsPosition[i]].value, "C") != 0))
    {
      return cardsPosition[i];
    }
  }

  //Verifica se possui JOKER para descartar
  for(int i = 1; i <= cardsPosition[0]; i++)
  {
    if(strcmp(myHand.cards[cardsPosition[i]].value, "C") == 0)
    {
      return cardsPosition[i];
    }
  }

  //Verifica se possui ACE para descartar
  for(int i = 1; i <= cardsPosition[0]; i++)
  {
    if(strcmp(myHand.cards[cardsPosition[i]].value, "A") == 0)
    {
      return cardsPosition[i];
    }
  }
  
  return -1;
}

// int makeAChoice(Hand myHand, Game *game)
// {
//   int *cardsPosition = cardsPositionCanIDiscard(myHand, game);
//   int cardPosition = hasTheCard(myHand, game->table);
//   if (cardPosition >= 0)
//     return cardPosition;

//   int cardNaipe = 0;

//   for (int i = 0; i < myHand.tam; i++)
//   {
//     cardNaipe = convertCardToInt(myHand.cards[i]);
//     if ((cardNaipe == JOKER || cardNaipe == ACE))
//     {
//       return i;
//     }
//   }
//   return -1;
// }

// int *cardsPositionCanIDiscard(Hand myHand, Game *game)
// {
//   int *cardsPosition = malloc(sizeof(int));
//   int qtd = 0;
//   cardsPosition[0] = 0;

//   for (int i = 0; i < myHand.tam; i++)
//   {
//     if (canDiscardThisCard(myHand.cards[i], game->table))
//     {
//       qtd += 1;
//       cardsPosition = realloc(cardsPosition, (sizeof(int) * (qtd + 1)));
//       cardsPosition[qtd] = i;
//       cardsPosition[0] = qtd;
//     }
//   }

//   return cardsPosition;
// }