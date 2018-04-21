#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "formules.h"

/* Sections formules */

Formule new_formule(void){
  Formule *f = malloc(sizeof(Formule));
  if (f==NULL)
    return (Formule) {NULL,NULL};
  return *f;
}

bool is_empty_formule(const Formule * f){
  return f == NULL;
}

int count_var_in_formule(const Formule * f){
  Clause *distinct_var = NULL;
  Clause *c_iter = NULL;
  int l=0;
  for(; f != NULL; f = f->next)
    for (c_iter = f->c; c_iter != NULL; c_iter++)
      push_var(&distinct_var,c_iter->v);
  //On utilise le fait que push_var n'ajoute une variable que si elle n'est pas présente
  l = length(distinct_var);
  free_clause(&distinct_var);
  return l;
}

int count_clause_in_formule(const Formule *f){
  int i = 0;
  for(;f!= NULL;f=f->next)
    i++;
  return i;
}

//Ajout en fin pour liste chainée de formules
int push_clause(Formule **f,Clause *c){
  if (*f == NULL){
    *f = malloc(sizeof(Formule));
    if(f == NULL){
      puts("Impossible d'allouer la formule");
      return -1;
    }
    (*f)->c = clause_copy(c);
    return 0;
  }
  else if (equal_clause((*f)->c,c))
    return 1;
  else
    return push_clause(&(*f)->next,c);
}

//Recursively free f
void free_formule(Formule **f){
  if (*f == NULL)
    return;
  else{
    free_clause(&((*f)->c));
    free_formule(&((*f)->next));
    free(*f);
  }
}

//Not Recursively print f
void print_formule(const Formule *f){
  if (is_empty_formule(f)){
    puts("Vide");
  }
  else{
    puts("------DEBUT :");
    for (;f != NULL; f=f->next){
      print_clause(f->c);
      if (f->next != NULL)
	puts("\nET");
    }
    puts("\n------FIN");
  }
}

void to_3sat(Formule **f){
  int new_id = count_var_in_formule(*f);

  /*Et là je me demande est-ce que je vous laisse finir l'algo 3 sat...
   Je vais déjà tout poster sur le github pour voir
Au fait l'algo est : http://inf242.forge.imag.fr/SAT-3SAT-and-other-red.pdf
Si vous  êtes motivés */
}
