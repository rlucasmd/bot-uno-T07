#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "hand.h"
#include "cards.h"
#include "game.h"
#include "strategy.h"

/** Constantes para as strings a serem lidas */
void debug(char *message) { fprintf(stderr, "%s\n", message); }

void printHand(Hand myHand)
{
  int last = myHand.tam - 1;
  fprintf(stderr, "[");
  for (int i = 0; i < last; i++)
  {
    fprintf(stderr, " %s%s,", myHand.cards[i].value, myHand.cards[i].naipe);
  }
  fprintf(stderr, " %s%s ]\n", myHand.cards[last].value, myHand.cards[last].naipe);
}

int hasSecondComplement(Card table)
{
  int a = strcmp(table.value, "A");
  int c = strcmp(table.value, "C");
  if (a == 0 || c == 0)
    return 1;
  return 0;
}

void readAction(char *action, char *complement, char *secondComplement, Game *game)
{
  if (strcmp(action, "DISCARD") == 0)
  {
    game->table = makeCard(complement);
    if (hasSecondComplement(game->table))
    {
      scanf("%s\n", secondComplement);
    }
  }
}

void printTable(Card table)
{
  char *tableCard = strcat(table.value, table.naipe);
  debug(tableCard);
}

int main()
{

  char temp[MAX_LINE];     // string para leitura temporária de dados
  char my_id[MAX_ID_SIZE]; // identificador do seu bot
  Hand myHand;
  Game *game = malloc(sizeof(Game));
  Card discardedCard;
  int position;

  setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===

  scanf("PLAYERS %[^\n]\n", temp);
  readPlayers(temp, game);

  scanf("YOU %s\n", my_id);

  scanf("HAND %[^\n]\n", temp);
  myHand = readHand(temp);

  scanf("TABLE %s", temp);
  game->table = readTable(temp);

  // === PARTIDA ===

  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char *secondComplement = (char *)malloc(sizeof(char) * (MAX_LINE + 1));

  strcpy(secondComplement, "");

  while (1)
  {
    do
    {

      scanf("%s %s", action, complement);
      readAction(action, complement, secondComplement, game);
      if (strcmp(action, "DISCARD") == 0)
      {
        int isDrawCard = convertCardToInt(makeCard(complement));
        if (isDrawCard == JACK || isDrawCard == JOKER)
        {
          game->shouldBuySomeCard = 1;
        }
        if (isDrawCard == ACE || isDrawCard == JOKER)
        {
          strcpy(game->table.naipe, secondComplement);
        }
      }

      if (strcmp(action, "BUY") == 0)
      {
        game->shouldBuySomeCard = 0;
      }

        } while (strcmp(action, "TURN") || strcmp(complement, my_id));

    int specialCard = convertCardToInt(game->table);
    if (game->shouldBuySomeCard)
    {
      switch (specialCard)
      {
      case JACK:
        printf("BUY 2\n");
        myHand = buyNCards(myHand, 2);
        break;
      case JOKER:
        printf("BUY 4\n");
        myHand = buyNCards(myHand, 4);
      }
    }
    else
    {
      position = makeAChoice(myHand, game);
      if (position >= 0)
      {
        game->table = myHand.cards[position];
        discardedCard = myHand.cards[position];
        myHand = cardToDiscard(position, myHand, game);
      }
      else
      {
        printf("BUY 1\n");
        myHand = buyNCards(myHand, 1);
      }
    }

    game->shouldBuySomeCard = 0;
  }

  free(myHand.cards);
  free(game);

  return 0;
}
