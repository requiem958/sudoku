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

//Ajout en fin pour liste chainée de formules
int push_clause(Formule **f,Clause * c){
  if (f == NULL){
    **f = new_formule();
    if(f == NULL){
      puts("Impossible d'allouer la formule");
      return;
    }
  }
  //push_clause with clauses functions
}

//Recursively free f
void free_formule(Formule **f){
  free(f);
}

//Recursively print f
void print_formule(const Formule *f){
  if (is_empty_formule(f)){
    puts("Vide");
  }
  else{
    puts("------DEBUT :");
    for (;f != NULL; f=f->next){
      print_clause(&f->c);
      if (f->next != NULL)
	puts("\nET");
    }
    puts("\n------FIN");
  }
}
