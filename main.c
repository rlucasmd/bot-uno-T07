#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Constantes para as strings a serem lidas */
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

enum GameCards
{
  ACE = 1,
  JACK = 11,
  QUEEN = 12,
  KING = 13,
  JOKER = 14,
};

typedef struct
{
  char value[5];
  char naipe[5];
} Card;

// typedef struct
// {
//   Card cardOnTable;
//   char actualNaipe[5];
// } Table;

typedef struct
{
  Card *cards;
  int tam;
} Hand;

typedef struct
{
  char players[10][MAX_ID_SIZE];
  int players_count;
  Card table;
  int shouldBuySomeCard;
} Game;

Card makeCard(char *string)
{
  Card my_card;
  char *substring;
  char *parte;
  char *aux1;

  aux1 = malloc(sizeof(char) * (strlen(string) + 1));
  strcpy(aux1, string);
  aux1[strlen(string)] = '\0';

  substring = strstr(aux1, "♥");
  if (substring != NULL)
  {
    parte = strtok(aux1, "♥");
    strcpy(my_card.naipe, "♥");
    my_card.naipe[strlen("♥")] = '\0';
  }
  else
  {
    substring = strstr(aux1, "♦");
    if (substring != NULL)
    {
      parte = strtok(aux1, "♦");
      strcpy(my_card.naipe, "♦");
      my_card.naipe[strlen("♦")] = '\0';
    }
    else
    {
      substring = strstr(aux1, "♣");
      if (substring != NULL)
      {
        parte = strtok(aux1, "♣");
        strcpy(my_card.naipe, "♣");
        my_card.naipe[strlen("♣")] = '\0';
      }
      else
      {
        substring = strstr(aux1, "♠");
        if (substring != NULL)
        {
          parte = strtok(aux1, "♠");
          strcpy(my_card.naipe, "♠");
          my_card.naipe[strlen("♠")] = '\0';
        }
      }
    }
  }
  strcpy(my_card.value, parte);
  my_card.value[strlen(parte)] = '\0';
  return my_card;
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

void debug(char *message) { fprintf(stderr, "%s\n", message); }

Hand reallocateNCard(Hand myHand, int n)
{
  int tam = myHand.tam + n;
  myHand.cards = realloc(myHand.cards, (sizeof(Card)) * (tam));
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

int hasScondComplement(Card table)
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
    if (hasScondComplement(game->table))
    {
      scanf("%s\n", secondComplement);
    }
  }
}

int cardToInt(Card table)
{
  int isV = strcmp(table.value, "V");
  if (isV == 0)
    return JACK;
  int isC = strcmp(table.value, "C");
  if (isC == 0)
    return JOKER;
  return 0;
}
int cardToInt2(Card card)
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

int checkNaipe(Hand myHand, char *complement)
{
  for (int i = 0; i < myHand.tam; i++)
  {
    if (strcmp(myHand.cards[i].naipe, complement) == 0)
    {
      return i;
    }
  }

  return -1;
}

char *choseNaipe(int i)
{
  if (i == 0)
    return "♥";
  if (i == 1)
    return "♦";
  if (i == 2)
    return "♣";
  return "♠";
}

int naipeToInt(char *naipe)
{
  if (strcmp(naipe, "♥") == 0)
    return 0;
  if (strcmp(naipe, "♦") == 0)
    return 1;
  if (strcmp(naipe, "♣") == 0)
    return 2;
  return 3;
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
  int needsComplement = 0;
  int mostNaipeOnHand = countNaipesOnHand(myHand);
  switch (cardToInt2(card))
  {
  case JOKER:
    needsComplement = 1;
    break;
  case ACE:
    needsComplement = 1;
    break;
  default:
    needsComplement = 0;
    break;
  }
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

int isAce(Card card)
{
  if (strcmp(card.value, "A") == 0)
  {
    return 1;
  }
  return 0;
}

int makeAChoice(Hand myHand, Game *game)
{
  int cardPosition = hasTheCard(myHand, game->table);
  if (cardPosition >= 0)
    return cardPosition;

  int cardNaipe = 0;

  for (int i = 0; i < myHand.tam; i++)
  {
    cardNaipe = cardToInt2(myHand.cards[i]);
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
        int isDrawCard = cardToInt2(makeCard(complement));
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
    printTable(game->table);
    // agora é a vez do seu bot jogar
    int specialCard = cardToInt2(game->table);
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
        // if (strcmp(secondComplement, "") != 0)
        //   strcpy(table.naipe, secondComplement);

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
