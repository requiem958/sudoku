#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "clauses.h"

Clause new_clause(){
  Clause *c = malloc(sizeof(Clause));
  return *c;
}

// tail-rec fun, with nested functions (not allowed with pedantic)
int length(Clause *c){
  int rec_length(Clause *c, int acc){
    if (c==NULL)
      return acc;
    else
      return rec_length(c->next,acc+1);
  }
  return rec_length(c,0);
}

int push_var(Clause **c, Variable v){
  if (*c==NULL){
    *c = malloc(sizeof(Clause));
    if (!*c)
      return -1;
    (*c)->v = v;
    return 0;
  }
  else if (VAR_EQ((*c)->v,v))
    return 1;
  else
    return push_var(&(*c)->next,v);
  
}

int pop_var(Clause **c, Variable *v){
  if (*c==NULL)
    return -1;
  if ((*c)->next == NULL){
    free(*c);
    *c = NULL;
    return 1;
  }

  while ((*c)->next->next != NULL)
    c = &(*c)->next;
  *v = (*c)->next->v;
  free((*c)->next);
  (*c)->next=NULL;
  return 0;
}

Clause* del_var(Clause** c, const Variable v){
  Clause* iter = *c;
  Clause* temp = NULL;
  if (*c == NULL)
    return *c;

  if (VAR_EQ((*c)->v,v)){
    temp = (*c)->next;
    free(*c);
    return temp;
  }
  
  while(iter->next != NULL){
    if (VAR_EQ(iter->next->v,v)){
      temp = iter->next->next;
      free(iter->next);
      iter->next = temp;
      return *c;
    }
    iter = iter->next;
  }

  return *c;
}

bool is_valid(const Clause *c){
  const Clause *p=c->next;

  while(c != NULL){
    p= c->next;
    while(p != NULL){
      if (VAR_EQ_NOT(c->v,p->v))
	return true;
      p = p->next;
    }
    c = c->next;
  }
  return false;
}
void free_clause(Clause **c){
  if (*c == NULL)
    return;
  else{
    free_clause(&(*c)->next);
    (*c)->next = NULL;
    free(*c);
    *c = NULL;
  }
}

bool is_empty_clause(const Clause* c){
  return c == NULL;
}

void print_clause(const Clause* c){
  unsigned int i = 0;
  if (is_empty_clause(c))
    puts("Vide");
  else{
    for (; c != NULL; c = c->next){
      afficher_variable(&c->v);
      if(c->next != NULL)
	fputs("OU",stdout);
    }
  }
}
