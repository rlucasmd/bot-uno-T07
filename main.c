#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

/** Constantes para as strings a serem lidas */
void debug(char *message) { fprintf(stderr, "%s\n", message); }

Hand reallocateNCard(Hand myHand, int n)
{
  int tam = myHand.tam + n;
  myHand.cards = realloc(myHand.cards, (sizeof(Card)) * (tam));
  return myHand;
}
char *choseNaipe(int i)
{
  if (i == HEART)
    return "♥";
  if (i == DIAMONDS)
    return "♦";
  if (i == CLUB)
    return "♣";

  return "♠";
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

Card makeCard(char *string)
{
  char *suits[4];
  Card myCard;
  char *naipe;
  char *aux = (char *)malloc(sizeof(char) * (strlen(string) + 1));
  strcpy(aux, string);

  for (int i = 0; i < 4; i++)
  {
    suits[i] = (char *)malloc(sizeof(char) * 4);
    strcpy(suits[i], choseNaipe(i));
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
Hand buyNCards(Hand myHand, int n)
{
  char read[5];
  int tam = myHand.tam;
  myHand = reallocateNCard(myHand, n);
  for (int i = tam; i < tam + n; i++)
  {
    scanf(" %[^\n]\n", read);
    myHand.cards[i] = makeCard(read);
    myHand.tam += 1;
  }
  return myHand;
}

Hand readHand(char *entrada)
{
  Hand myHand;
  myHand.tam = 7;
  myHand.cards = malloc(sizeof(Card) * 7);
  char *aux[7];
  char *parte;

  parte = strtok(entrada, "[ ");

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

Hand discard(Hand myHand, Card card)
{
  int tam = myHand.tam;
  int comp_value;
  int comp_naipe;
  for (int i = 0; i < tam; i++)
  {
    comp_value = strcmp(myHand.cards[i].value, card.value);
    comp_naipe = strcmp(myHand.cards[i].naipe, card.naipe);
    if (comp_value == 0 && comp_naipe == 0)
    {
      for (int j = i; j < tam - 1; j++)
      {
        myHand.cards[j] = myHand.cards[j + 1];
      }
      myHand = reallocateNCard(myHand, -1);
      myHand.tam -= 1;
      break;
    }
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

int canDiscardThisCard(Card table, Card handCard)
{
  int result = (strcmp(table.naipe, handCard.naipe) == 0) ||
               (strcmp(table.value, handCard.value) == 0);

  return result;
}

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

int countNaipesOnHand(Hand myHand)
{
  int naipes[4] = {0};
  int num;
  for (int i = 0; i < myHand.tam; i++)
  {
    num = naipeToInt(myHand.cards[i].naipe);
    naipes[num] += 1;
  }
  int bigger = -1;
  for (int i = 0; i < 3; i++)
  {
    if (bigger < naipes[i])
    {
      bigger = i;
    }
  }
  return bigger;
}

Hand cardToDiscard(Card card, Hand myHand, Game *game)
{
  int cardInt = convertCardToInt(card);
  int needsComplement = (cardInt == JOKER) || (cardInt == ACE);
  int mostNaipeOnHand = countNaipesOnHand(myHand);

  if (needsComplement)
  {
    char *naipe = choseNaipe(mostNaipeOnHand);
    strcpy(game->table.naipe, naipe);

    printf("DISCARD %s%s %s\n", card.value, card.naipe, naipe);
    myHand = discard(myHand, card);
  }
  else
  {
    printf("DISCARD %s%s\n", card.value, card.naipe);
    myHand = discard(myHand, card);
  }

  return myHand;
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
    // printTable(game->table);
    // agora é a vez do seu bot jogar
    printHand(myHand);
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
          myHand = cardToDiscard(discardedCard, myHand, game);
        }
        else
        {
          printf("BUY 1\n");
          myHand = buyNCards(myHand, 1);
        }
      }
      else
      {
        position = makeAChoice(myHand, game);
        if (position >= 0)
        {
          game->table = myHand.cards[position];
          discardedCard = myHand.cards[position];
          myHand = cardToDiscard(discardedCard, myHand, game);
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
