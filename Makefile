BOT_NAME=bot_D
PARAMS= -g -W -pedantic

all: main.c debugger hand cards strategy game 
	gcc main.c hand.o cards.o game.o strategy.o debugger.o -o $(BOT_NAME) $(PARAMS)
hand: hand.c
	gcc hand.c -c $(PARAMS) 
cards: cards.c
	gcc cards.c -c $(PARAMS)
game: game.c
	gcc game.c -c $(PARAMS)
strategy: strategy.c
	gcc strategy.c -c $(PARAMS)
debugger: debugger.c
	gcc debugger.c -c $(PARAMS)
clean: 
	rm -rf *.o
run: 
	./uno bot_C bot_F bot_A bot_D -s 50882 -v
