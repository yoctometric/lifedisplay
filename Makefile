CC = gcc
CFLAGS = -Wall -O2

all:	test_display test_buttons game

###

conway.o:	conway.c conway.h
	$(CC) $(CFLAGS) -c -g conway.c

###

test_display:	ht16K33.o test_display.o
	$(CC) -o test_display test_display.o ht16K33.o

ht16K33.o: ht16K33.h ht16K33.c
	$(CC) $(CFLAGS) -c -g ht16K33.c

test_display.o:	ht16K33.h test_display.c
	$(CC) $(CFLAGS) -c -g test_display.c

###

game:	game.o conway.o ht16K33.o
	$(CC) -o game conway.o ht16K33.o game.o

game.o:	game.h conway.h ht16K33.h game.c
	$(CC) $(CFLAGS) -c -g game.c

###

test_buttons:	buttons.o test_buttons.o
	$(CC) -o test_buttons test_buttons.o buttons.o

buttons.o:	buttons.h buttons.c
	$(CC) $(CFLAGS) -c -g buttons.c

test_buttons.o:	buttons.h test_buttons.c
	$(CC) $(CFLAGS) -c -g test_buttons.c

###

