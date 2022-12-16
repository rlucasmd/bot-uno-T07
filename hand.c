//funções que "operam" no nível da estrutura da hand
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "cards.h"
#include "strategy.h"

// Realoca o vetor das cartas de uma mão 
Hand reallocateNCards(Hand myHand, int n)
{
  int tam = myHand.tam + n;
  myHand.cards = realloc(myHand.cards, (sizeof(Card)) * (tam));
  return myHand;
}
// Lê e adiciona n cartas à mão
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

//retira a carta descartada da mão do bot
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
// Verifica se pode descartar uma carta da mão
int canDiscardThisCard(Card table, Card handCard)
{
  int result = (strcmp(table.naipe, handCard.naipe) == 0) ||
               (strcmp(table.value, handCard.value) == 0);

  return result;
}
// Verifica se tem uma carta que possa ser jogada com base na carta do table
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
// Realiza a ação de descartar uma carta previamente selecionada
Hand cardToDiscard(int position, Hand myHand, Game *game)
{
  int cardInt = convertCardToInt(myHand.cards[position]);
  int needsComplement = (cardInt == JOKER) || (cardInt == ACE);
  int mostNaipeOnHand = countNaipesOnHand(myHand); //verifica o naipe que mais possui na mão para caso precise escolher um ao jogar um A ou C
  Card discardedCard = myHand.cards[position];

  if (needsComplement) //Caso o descarte seja A ou C
  {
    char *naipe = choseNaipe(mostNaipeOnHand);
    strcpy(game->table.naipe, naipe);
    if (cardInt == QUEEN)
    {
      game->flux *= -1;
    }

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

int isTheSameCard(Card firstCard, Card secondCard)
{
  if (strcmp(firstCard.value, secondCard.value) == 0 && strcmp(firstCard.naipe, secondCard.naipe) == 0)
    return 1;
  return 0;
}
