OPT=-Wall -Wextra -O3
CC=gcc $(OPT)
DEBUG=-g

all: main

to_dimacs.o: to_dimacs.c to_dimacs.h formules.h
	$(CC) $(DEBUG) -c $<

types.o: types.c types.h
	$(CC) $(DEBUG) -c $<

clauses.o: clauses.c clauses.h types.h
	$(CC) $(DEBUG) -c $<

formules.o: formules.c formules.h clauses.h types.h
	$(CC) $(DEBUG) -c $<

liresudoku.o: liresudoku.c liresudoku.h
	$(CC) $(DEBUG) -c $<

main: main.c formules.o clauses.o types.o to_dimacs.o
	$(CC) -o $@ $^

clean:
	rm main *.o *~
