BOT_NAME=bot_C
PARAMS= -g -W -pedantic

all: main.c hand cards strategy game 
	gcc main.c hand.o cards.o game.o strategy.o -o $(BOT_NAME) $(PARAMS)
hand: hand.c
	gcc hand.c -c $(PARAMS)
cards: cards.c
	gcc cards.c -c $(PARAMS)
game: game.c
	gcc game.c -c $(PARAMS)
strategy: strategy.c
	gcc strategy.c -c $(PARAMS)
