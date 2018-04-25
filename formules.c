#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "formules.h"


static Variable* init_fvar (unsigned int ind);
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
<<<<<<< HEAD
    for (c_iter = f->c; c_iter != NULL; c_iter = c_iter->next)
=======
    for (c_iter = f->c; c_iter != NULL; c_iter=c_iter->next)
>>>>>>> master
      push_var(&distinct_var,c_iter->v);
  //On utilise le fait que push_var n'ajoute une variable que si elle n'est pas présente
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

static Variable init_fvar (unsigned int ind){
  Variable a;
  a->id = ind ;
  a->n=-1;
  a->l=-1;
  a->c=-1;
  a->neg=true;
  return a;
}
#define initc(x) x =(Clause *) malloc(sizeof(Clause));x->next =(Clause *) malloc(sizeof(Clause));x->next->next =(Clause *) malloc(sizeof(Clause))
#define initv(x,y) x = init_fvar (ind);y=init_fvar (ind);y->neg=false;ind++;


void to_3sat(Formule **f){
  const Formule *head = *f;
  unsigned int  ind,ln,i;
  Clause *x,*w;
  Variable *a,*b,*Na,*Nb;
  //Pour l'écriture dans le fichier dimacs on peut pas avoir des indices négatifs, donc on prend des indices
  //Strictement supérieurs à l'indice max possible, or formule est déjà entiérement rempli donc l'indice max est le nombre de var <=> nb indice
  ind=count_var_in_formule(*f)+1;
  while (*f!=NULL){
    ln = length((*f)->c);
    
    if (ln==1){
      initc(x);
      initv(a,Na);
      initv(b,Nb);
      // cas -z1 y1 -z2
      push_var(&((*f)->c->next), *a);
      push_var(&((*f)->c->next), *b);
      // cas z1 y1 z2
      x->v= *a;
      x->next->v= (*f)->c->v;
      x->next->next->v=*b;
      push_clause(f,x);
      initc(x);// cas -z1 y1 z2
      x->v= *a;
      x->next->v= (*f)->c->v;
      x->next->next->v=*b;
      push_clause(f,x);
      initc(x);// cas z1 y1 -z2
      x->v= *a;
      x->next->v= (*f)->c->v;
      x->next->next->v=*b;
      push_clause(f,x);
    }else if (ln==2){
      initc(x);
      initv(a,Na);
      // cas y1 y2 z1
      (*f)->c->next->next->v=*a;
      //cas y1 y2 -z1
      x->v= *Na;
      x->next->v= (*f)->c->v;
      x->next->next->v=(*f)->c->next->v;
      push_clause(f,x);
    }else if (ln>3){
      w =(Clause *) malloc(sizeof(Clause));//y1 y2 z1
      initv(a,Na);
      w= (*f)->c->next->next;
      (*f)->c->next->next->v= *a;
      (*f)->c->next->next->next=NULL;
      for (i=4;i<ln;i++){// -zk-2 yk zk-1
	initc(x);
	initv(b,Nb);
	x->v= *Na;
	x->next->v=w->v;
	w=w->next;
	x->next->next->v=*b;
	a=b;
	Na=Nb;
	push_clause(f,x);
      }
      initc(x);// yn zn zn+1
      x->v=*Na;
      x->next->v=w->v;
      x->next->next->v=w->next->v;
      push_clause(f,x);
    }
    f=&(*f)->next;
    free_clause(&c);
    free(a);
    free(b);
    free(Na);
    free(Nb);
  }
  //Au fait l'algo est : http://inf242.forge.imag.fr/SAT-3SAT-and-other-red.pdf
}
