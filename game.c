#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "debugger.h"
#include "cards.h"
// lê as cartas iniciais do jogo distribuídas pelo gerenciador
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
// lê a carta inicial da mesa
Card readTable(char *entrada)
{
  Card aux = makeCard(entrada);
  return aux;
}
// lê os jogadores participantes da partida e guarda em variáveis struct cada jogador
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
// verifica se a carta descartada na mesa é do tipo que precisa de um segundo complemento (carta de alção Às ou Coringa)
int hasSecondComplement(Card table)
{
  int card = convertCardToInt(table);
  if (card == ACE || card == JOKER)
    return 1;
  return 0;
}
// lê a ação do jogo e atualiza o gerenciador game(struct que contem a lógica de
// quem está jogando, quem é o próximo a jogar e quem foi o último a jogar,
// também guardar informações da carta sobre a mesa, sentido de rotação)
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
// transforma a ação lida pelo bot e converte pra um ENUM do tipo action;
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
// atualiza o indice do bot que irá jogar
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
// caso o jogador atual realize uma compra de 1 carta, atualiza o vetor de cartas
// que possivelmente o bot não teria, baseado na carta sobre a mesa.
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
// atualiza algumas informações da partida, baseado na action enviada pelo gerenciador:
//    TURN - atualiza o indice de qual bot está jogando atualmente.
//    DISCARD - identifica qual bot descartou a carta e atualiza a quantidade de cartas
//    que o bot possui na mão.
//    se for uma carta de compra (Valete ou Coringa) armazena uma flag pra o sabermos
//    se nosso bot deve comprar cartas, caso seja detectado que outro bot realizou a
//    compra, seguimos jogando normalmente.
//    BUY - atualiza a quantidade de cartas na mão do bot que realizou a compra,
//    também é realizado a liberação da flag shouldBuySomeCard do nosso bot, pois outro
//    bot já realizou a compra e a carta descartada já cumpriu sua função.

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

    game->shouldBuySomeCard = 0;
  }
  // atualiza o index do jogador e as variáveis do próximo bot e do bot anterior
  if (game->botTurnIndex >= 0)
  {
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