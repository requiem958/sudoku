#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "to_dimacs.h"
#include "liresudoku.h"
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
    for (c_iter = f->c; c_iter != NULL; c_iter = c_iter->next)
      push_var(&distinct_var,c_iter->v);
  //On utilise le fait que push_var n'ajoute une variable que si elle n'est pas prÃ©sente
  l = length(distinct_var);
  free_clause(&distinct_var);
  return l;
}

int count_clauses_in_formule(const Formule *f){
  int i = 0;
  for(;f!= NULL;f=f->next)
    i++;
  return i;
}

//Ajout en fin pour liste chainÃ©e de formules
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

static Variable init_fvar (unsigned int ind){
  Variable a;
  a.id = ind ;
  a.n=-1;
  a.l=-1;
  a.c=-1;
  a.neg=false;
  return a;
}
#define initv(x,y) x = init_fvar (ind);y=init_fvar (ind);y.neg=true;ind++;


void to_3sat(Formule **f){
  Formule *iter = NULL;
  unsigned int  ind,ln,i;
  Clause *x=NULL,*w=NULL;
  Variable a,Na;
  Variable b,Nb;
  ind=coord_to_number(MAX+1,MAX+1,MAX+1,0);
  for (iter = *f; iter != NULL; iter= iter->next){
    switch(ln =length(iter->c)){
    case 1:
      /* Creation des variables fraiches */
      initv(a,Na); //z1 et -z1
      initv(b,Nb); //z2 et -z2
      /* On ajoute à f les nouvelles clauses */
      // Modification de la clause originale y1 -> -z1 y1 -z2
      push_var(&iter->c->next, Na);
      push_var(&iter->c->next, Nb);
      // Ajout de la clause  z1 y1 z2
      push_var(&x,a);
      push_var(&x,iter->c->v);
      push_var(&x,b);
      push_clause(f,x);
      free_clause(&x);
      // Ajout de la clause -z1 y1 z2
      push_var(&x,Na);
      push_var(&x,iter->c->v);
      push_var(&x,b);
      push_clause(f,x);
      free_clause(&x);
      // Ajout de la clause  z1 y1 -z2
      push_var(&x,a);
      push_var(&x,iter->c->v);
      push_var(&x,Nb);
      push_clause(f,x);
      break;
    case 2:
      initv(a,Na);
      // Modification de la clause originale y1 y2 -> y1 y2 z1
      push_var(&iter->c,a);
      // Ajout de la clause y1 y2 -z1
      push_var(&x,iter->c->v);
      push_var(&x,iter->c->next->v);
      push_var(&x,Na);
      push_clause(f,x);
      break;
    case 3:
      break;
    default:
      //Clause originale y1 y2 y3 ... yn
      //On sauvegarde y3 ... yn
      w = iter->c->next->next;
      //On coupe le lien entre y2 et y3
      iter->c->next->next = NULL;
      // On crée z1 et -z1 qu'on va ajouter a y1 y2 -> y1 y2 z1
      initv(a,Na);
      push_var(&iter->c,a);
      for (i=4;i<ln;i++){// -z(i-3) y(i-1) z(i-2)
	initv(b,Nb);
	push_var(&x,Na); //-z(i-3)
	push_var(&x,w->v); //yi-1
	push_var(&x,b); //z(i-2)
	push_clause(f,x);
	free_clause(&x);
	
	//z(i-3) <- z(i-2)
	a=b;
	Na=Nb;
	//y(i-1) <- y(i)
	w= del_var(&w,w->v);
      }
      //Phase finale: -z(n-3) yn-1 yn
      push_var(&x,Na);
      push_var(&x,w->v);
      push_var(&x,w->next->v);
      push_clause(f,x);
    }
    if (x != NULL)
      free_clause(&x);
  }
  //Au fait l'algo est : http://inf242.forge.imag.fr/SAT-3SAT-and-other-red.pdf
}
