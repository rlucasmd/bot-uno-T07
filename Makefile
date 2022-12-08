BOT_NAME=bot_C

all: main.c hand cards strategy game 
	gcc main.c hand.o cards.o game.o strategy.o -o $(BOT_NAME) -g -W -pedantic
hand: hand.c
	gcc hand.c -c -g -W -pedantic
cards: cards.c
	gcc cards.c -c -g -W -pedantic
game: game.c
	gcc game.c -c -g -W -pedantic
strategy: strategy.c
	gcc strategy.c -c -g -W -pedantic
