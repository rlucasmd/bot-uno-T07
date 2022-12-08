BOT_NAME=bot_C
PARAMS= -g -W -pedantic

all: main.c hand cards strategy game move 
	gcc main.c bin/hand.o bin/cards.o bin/game.o bin/strategy.o -o $(BOT_NAME) $(PARAMS)
hand: hand.c
	gcc hand.c -c $(PARAMS) 
cards: cards.c
	gcc cards.c -c $(PARAMS)
game: game.c
	gcc game.c -c $(PARAMS)
strategy: strategy.c
	gcc strategy.c -c $(PARAMS)
move: 
	mv *.o ./bin
