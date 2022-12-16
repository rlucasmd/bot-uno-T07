//Módulo principal, é quem inicializa as variáveis e chama as funções no momento adequado do jogo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "hand.h"
#include "cards.h"
#include "game.h"
#include "strategy.h"
#include "debugger.h"

/** Constantes para as strings a serem lidas */
int main()
{

  char temp[MAX_LINE]; // string para leitura temporária de dados

  Hand myHand;
  Game *game = malloc(sizeof(Game));
  game->gameAction = malloc(sizeof(GameAction));
  Card discardedCard;
  int position;

  setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===

  scanf("PLAYERS %[^\n]\n", temp);
  readPlayers(temp, game);

  scanf("YOU %s\n", game->myId);

  scanf("HAND %[^\n]\n", temp);
  myHand = readHand(temp);

  scanf("TABLE %s", temp);
  game->table = readTable(temp);
  game->flux = 1;

  // === PARTIDA ===

  while (1)
  {
    do
    { //Loop de observação, comportamento do bot enquanto não está jogando
      readAction(game);
      updateGame(game);
    } while (strcmp(game->gameAction->action, "TURN") || strcmp(game->gameAction->complement, game->myId));
    //Loop de comportamento do bot no seu turno.
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
  free(game->gameAction);
  free(game);

  return 0;
}
