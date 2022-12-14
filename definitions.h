#ifndef DEF
#define DEF
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

enum Suits
{
  HEART = 0,
  DIAMONDS = 1,
  CLUB = 2,
  SPADE = 3,
};

enum Actions
{
  DISCARD = 0,
  BUY = 1,
  TURN = 2,
};

typedef struct
{
  char value[3];
  char naipe[5];
} Card;

typedef struct
{
  Card *cards;
  int tam;
} Hand;

typedef struct
{
  char botId[MAX_ID_SIZE];
  int cardsQuantity;
  Hand buyedHand;
} Player;

typedef struct
{
  char action[10];
  char complement[10];
  char secondComplement[10];
} GameAction;

typedef struct
{
  char myId[MAX_ID_SIZE];
  Player players[6];
  int playersCount;
  int botTurnIndex;
  int flux;
  Player nextBot, previousBot;
  Card table;
  int shouldBuySomeCard;
  GameAction *gameAction;
} Game;
#endif