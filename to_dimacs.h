#ifndef TO_DIMACS_H
#define TO_DIMACS_H

int coord_to_number(unsigned int l, unsigned int c, unsigned int n);
//renvoie id=taille d eligne carré fois l + taille de ligne *c + n 

int number_to_coord(unsigned int number, unsigned int *l, unsigned int *c, unsigned int *n);
// renvoie la colone 

void read_dimacs_file(char *dimacs_filename);
// lire un fichier d'expression logique voir internet format dimacs

void write_dimacs_file(char *dimacs_filename);
// ecrire toute les clauses 

#endif
