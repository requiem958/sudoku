CC=gcc
DEBUG=-g

all: main

to_dimacs.o: to_dimacs.c to_dimacs.h formules.h
	$(CC) $(DEBUG) -c $<

formules.o: formules.c formules.h
	$(CC) $(DEBUG) -c $<

liresudoku.o: liresudoku.c liresudoku.h
	$(CC) $(DEBUG) -c $<

main: main.c formules.o to_dimacs.o
	$(CC) -o $@ $^

clean:
	rm main *.o *~
