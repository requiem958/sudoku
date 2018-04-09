#include <stdio.h>
#include <stdlib.h>
#include "formules.h"

/* Sections formules */

formule* creer_formule(void){
  formule *f = malloc(sizeof(formule));
  if (f==NULL)
    return NULL;
  f->longueur = 0;
  return f;
}

bool is_empty_formule(const formule * f){
  return f == NULL || f->longueur == 0;
}

void form_push_var(formule *f, const unsigned int i, const Variable v){
  Clause * c = NULL;
  if (f == NULL){
    f = creer_formule();
    if(f == NULL){
      puts("Impossible d'allouer la formule");
      return;
    }
  }
  if (f->longueur == LEN_MAX_F){
    puts("Plus de place dans cette formule, augmenter LEN_MAX_F");
    return;
  }
  if (i==f->longueur)
    f->longueur++;

  c = &(f->clauses[i]);
  //push_var with clauses functions
}

void liberer_formule(formule *f){
  f->longueur = 0;
  free(f);
}

void reset_formule(formule *f){
  unsigned int i = 0,j = 0;
  Clause * iterator = NULL;
  f->longueur = 0;
  //TODO: iterate on each clause in f to destroy it (free_clause)
}

void afficher_formule(const formule *f){
  unsigned int i = 0;
  if (is_empty_formule(f)){
    puts("Vide");
  }
  else{
    puts("------DEBUT :");
    for (;i <= f->longueur-1; i++){
      print_clause(&f->clauses[i]);
      if (i != f->longueur-1)
	puts("\nET");
    }
    puts("\n------FIN");
  }
}
