#ifndef TO_DIMACS_H
#define TO_DIMACS_H

unsigned int coord_to_number(unsigned int l, unsigned int c, unsigned int n);
//renvoie id=taille d eligne carrÃ© fois l + taille de ligne *c + n 

int number_to_coord(unsigned int number, unsigned int *l, unsigned int *c, unsigned int *n);
// renvoie la colone 

void dimacs_to_sudoku(char *dimacs_file, char *sudoku_file,unsigned int sudoku_size);
//Ecrit le fichier sudoku correspondant à un fichier dimacs

void sudoku_to_dimacs(char *dimacs_file, char *sudoku_file);
//Ecrit le fichier dimacs correspondant à un fichier sudoku

#endif
