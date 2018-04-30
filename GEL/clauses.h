#ifndef CLAUSES_H_INCLUDED
#define CLAUSES_H_INCLUDED

#include "types.h"

typedef struct Clause{
  Variable v;
  struct Clause * next;
}Clause;


/*Create an empty clause */
Clause new_clause();

Clause* clause_copy(Clause *src);

/*Return number of var in c */
int length(Clause *c);

/*Add a var to c (if v already in c, not add) */
int push_var(Clause **c, Variable v);

/*Delete the last added var to c and stock it into v*/
int pop_var(Clause *c, Variable *v);

/*Delete the given var from c and return head of new c, nothing if var not in c*/
Clause* del_var(Clause** c, Variable v);

/* true if c contains a var and it's neg*/
bool is_valid(const Clause *c);

/*Free c from memory*/
void free_clause(Clause **c);

/* Return true only if c points to NULL*/
bool is_empty_clause(const Clause* c);

/* Print c in the form : NOT(var1.id) OU var2.id OU ....*/
void print_clause(const Clause* c);

bool equal_clause(Clause *c1, Clause *c2);

#endif
