.PHONY: clean

RN = rm -f

game : mainScreen.o rank.o hangman.o mainScreen.h rank.h
	gcc mainScreen.o rank.o hangman.o -lcurses -o game

hangman.o : hangman.c mainScreen.o rank.o mainScreen.h rank.h
	gcc -lcurses -c hangman.c

mainScreen.o : mainScreen.h mainScreen.c
	gcc -lcurses -c mainScreen.c

rank.o : rank.h rank.c
	gcc -lcurses -c rank.c

clean:
	$(RM) *.o
