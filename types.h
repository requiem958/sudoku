#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED


#include <stdbool.h>

typedef struct{
  /* unique coordonn�e dimacs*/
  unsigned int id;
  /* Triplet de coordonn�e sudoku */
  unsigned int l;
  unsigned int c;
  unsigned int n;
  /*neg == true => var is negative otherwise var isn't*/
  bool neg;
}Variable;

#define VAR_EQ(v1,v2) (v1.id == v2.id && v1.neg == v2.neg)

#define VAR_EQ_NOT(v1,v2) (v1.id == v2.id && v1.neg != v2.neg)
#endif
