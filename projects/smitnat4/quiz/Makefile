CC = gcc

CFLAGS = -Wall -pedantic -coverage -lm

all: testme
	./testme

testme: testme.c
	gcc $(CFLAGS) -o testme testme.c

clean:
	rm -f testme testme.c.gcov testme.gcda testme.gcno
