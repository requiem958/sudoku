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

void push_var(formule *f, const unsigned int i, const variable v){
  clause * c = NULL;
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

  if (c->longueur == LEN_MAX_C){
    puts("Plus de place dans la clause, augmenter LEN_MAX_C");
    return;
  }
  c->var[c->longueur++] = v;
}

void liberer_formule(formule *f){
  f->longueur = 0;
  free(f);
}

void reset_formule(formule *f){
  unsigned int i = 0,j = 0;
  clause * c = NULL;
  f->longueur = 0;
  for (;i < LEN_MAX_F-1;i++){
    c = &f->clauses[i];
    for (; j < LEN_MAX_C-1;j++){
      set_var_id(&c->var[j], 0);
      c->var[j].neg = FALSE;
    }
    c->longueur = 0;
  }
}

void afficher_formule(const formule *f){
  unsigned int i = 0;
  if (is_empty_formule(f)){
    puts("Vide");
  }
  else{
    puts("------DEBUT :");
    for (;i <= f->longueur-1; i++){
      afficher_clause(&f->clauses[i]);
      if (i != f->longueur-1)
	puts("\nET");
    }
    puts("\n------FIN");
  }
}

/*Section clauses */

bool is_empty_clause(const clause * c){
  return c == NULL || c->longueur == 0;
}

void afficher_clause(const clause *c){
  unsigned int i = 0;
  if (is_empty_clause(c)){
    puts("Vide");
  }
  else{
    for (;i <= c->longueur-1; i++){
      afficher_variable(&c->var[i]);
      if (i != c->longueur-1)
	fputs("OU",stdout);
    }
  }
}
/*Section variables */

bool neg_var(variable * v){
  if ( v != NULL)
    return v->neg = (v->neg == FALSE) ? TRUE : FALSE;
  return FALSE;
}

int set_var_id(variable *v, const int id){
  if (v != NULL)
    return v->id = id;
  return -1;
}

void afficher_variable(const variable * v){
  if (v==NULL)
    return;

  if (v->neg){
    printf(" NOT( x:%d ) ", v->id);
    return;
  }
  printf(" x:%d ", v->id);
}
