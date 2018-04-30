#ifndef FORMULES_H
#define FORMULES_H

#include <stdbool.h>
#include "types.h"
#include "clauses.h"

typedef struct Formule{
  Clause *c;
  struct Formule * next;
}Formule;


/*Create an empty clause */
Formule new_formule();

/*Return number of something in f */
int formule_length(Formule *f);

/*Add a clause to f (if c already in f, not add) */
int push_clause(Formule **f, Clause *c);

/*Delete the last added var to c and stock it into v*/
int pop_clause(Formule **f, Clause **c);

/*Delete the given clause from f and return head of new f, nothing if clause not in f*/
Clause* del_clause(Formule** f, Clause *c);

/* true if c contains a var and it's neg*/
bool formule_is_valid(const Formule *f);

/*Free c from memory*/
void free_formule(Formule **f);

/* Return true only if f points to NULL*/
bool is_empty_formule(const Formule* f);

/* Print f in the form : 
   print_clause(head)
ET
print_clause(head->next)
ET
...
 */
void print_formule(const Formule* c);

void to_3sat(Formule** f);

int count_var_in_formule(const Formule* f);

int count_clauses_in_formule(const Formule*f);

#endif
