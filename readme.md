# Possível separação em arquivos para modularização:

- hand
  - Hand reallocateNCards(Hand myHand, int n)
  - Hand buyNCards(Hand myHand, int n)
  - Hand discard(Hand myHand, int position)
  - int canDiscardThisCard(Card table, Card handCard)
  - int hasTheCard(Hand myHand, Card table)
  - Hand cardToDiscard(int position, Hand myHand, Game *game)
  
- cards (Arquivo responsável por manipular todas as operações de criação e manipulação das cartas)
  - char *choseNaipe(int n)
  - int naipeToInt(char *naipe)
  - Card makeCard(char *cardString)
  - int convertCardToInt(Card card)
  
- game (Arquivo responsável por ler todas as informações para se criar uma partida)
  - Hand readHand(char *inputString)
  - Card readTable(char *entrada)
  - void readPlayers(char *entrada, Game *game)

- strategy
  - int countNaipesOnHand(Hand myHand)
  - int makeAChoice(Hand myHand, Game *game)