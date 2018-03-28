CC=gcc
DEBUG=-g

all: main

formules.o: formules.c formules.h
	$(CC) $(DEBUG) -c $<

liresudoku.o: liresudoku.c liresudoku.h
	$(CC) $(DEBUG) -c $<

main: main.c formules.o
	$(CC) -o $@ $^

clean:
	rm main *.o *~
