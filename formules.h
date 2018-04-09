#ifndef FORMULES_H
#define FORMULES_H

#include <stdbool.h>
#include "types.h"
#include "clauses.h"
/* Constantes */

#define LEN_MAX_F 100

typedef struct formule_s {
  Clause clauses[LEN_MAX_F];
  unsigned int longueur;
} formule;

/* Definitions fonctions */

/* Fonctions sur formules */

formule * creer_formule(void);

bool is_empty_formule(const formule *f);

void form_push_var(formule *f, const unsigned int i, const Variable v);

void liberer_formule(formule *f);

void afficher_formule(const formule *f);

void reset_formule(formule *f);

#endif
