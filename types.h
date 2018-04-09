#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED


#include <stdbool.h>

typedef struct{
  /* unique coordonnée dimacs*/
  unsigned int id;
  /* Triplet de coordonnée sudoku */
  unsigned int l;
  unsigned int c;
  unsigned int n;
  /*neg == true => var is negative otherwise var isn't*/
  bool neg;
}Variable;

#define VAR_EQ(v1,v2) (v1.id == v2.id && v1.neg == v2.neg)

#define VAR_EQ_NOT(v1,v2) (v1.id == v2.id && v1.neg != v2.neg)

bool neg_var(Variable *v);

int set_var_id(Variable* v,const int id);

void afficher_variable(const Variable* v);

#endif
