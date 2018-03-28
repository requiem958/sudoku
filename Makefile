CC=gcc
DEBUG=-g

all: main

formules.o: formules.c formules.h
	$(CC) $(DEBUG) -c $<

sudoku.o: sudoku.c sudoku.h
	$(CC) $(DEBUG) -c $<

main: main.c formules.o
	$(CC) -o $@ $^

clean:
	rm main *.o *~
