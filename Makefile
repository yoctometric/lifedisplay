CC = gcc

all:	test_display conway

###

conway:	conway.o
	$(CC) -o conway conway.o

conway.o:	conway.c conway.h
	$(CC) -c -g conway.c

###

test_display:	ht16K33.o test_display.o
	$(CC) -o test_display test_display.o ht16K33.o

ht16K33.o: ht16K33.h ht16K33.c
	$(CC) -c -g ht16K33.c

test_display.o:	ht16K33.h test_display.c
	$(CC) -c -g test_display.c

###
