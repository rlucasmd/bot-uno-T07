#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "card.h"
#include "hand.h"

/** Constantes para as strings a serem lidas */
void debug(char *message) { fprintf(stderr, "%s\n", message); }

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

Card readTable(char *entrada)
{
  Card aux = makeCard(entrada);
  return aux;
}

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
      if (specialCard == JOKER || specialCard == ACE)
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
    }

    game->shouldBuySomeCard = 0;
  }

  free(myHand.cards);
  free(game);

  return 0;
}
