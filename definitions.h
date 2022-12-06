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
  char players[6][MAX_ID_SIZE];
  int players_count;
  Card table;
  int shouldBuySomeCard;
} Game;
#endif