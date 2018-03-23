#ifndef FORMULES_H
#define FORMULES_H

/* Constantes */

#define LEN_MAX_F 100
#define LEN_MAX_C 100

/* Definitions types*/

typedef enum { FALSE,TRUE } bool;

typedef struct var_s {
  /* unique coordonnée dimacs*/
  unsigned int id;
  /* Triplet de coordonnée sudoku */
  unsigned int l;
  unsigned int c;
  unsigned int n;
  /*Variable en négation ou non */
  bool neg;
}variable;

typedef struct clause_s {
  variable var[LEN_MAX_C];
  unsigned int longueur;
} clause;

typedef struct formule_s {
  clause clauses[LEN_MAX_F];
  unsigned int longueur;
} formule;

/* Definitions fonctions */

/* Fonctions sur formules */

formule * creer_formule(void);

bool is_empty_formule(const formule *f);

void push_var(formule *f, const unsigned int i, const variable v);

void pop_clause(formule *f);

void liberer_formule(formule *f);

void afficher_formule(const formule *f);

void reset_formule(formule *f);

/* Fonctions sur clauses */

bool is_empty_clause(const clause *c);

void afficher_clause(const clause * c);

/* Fonctions sur variables */

bool neg_var(variable *v);

int set_var_id(variable *v,const int id);

void afficher_variable(const variable * v);


#endif
