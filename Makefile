BOT_NAME=bot_C

PARAMS= -g -W -pedantic

all: main.c card hand
	gcc main.c card.o hand.o -o $(BOT_NAME) $(PARAMS)

card: card.c 
	gcc card.c -c $(PARAMS)

hand: hand.c
	gcc hand.c -c $(PARAMS)
