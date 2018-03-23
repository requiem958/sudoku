#ifndef TO_DIMACS_H
#define TO_DIMACS_H

int coord_to_number(unsigned int l, unsigned int c, unsigned int n);

int number_to_coord(unsigned int number, unsigned int *l, unsigned int *c, unsigned int *n);

void read_dimacs_file(char *dimacs_filename);

void write_dimacs_file(char *dimacs_filename);

#endif
