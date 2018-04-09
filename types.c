
#include <stdbool.h>
#include <stdio.h>
#include "types.h"

bool neg_var(Variable * v){
  if ( v != NULL)
    return v->neg = (v->neg == false) ? true:false;
  return false;
}

int set_var_id(Variable* v, const int id){
  if (v != NULL)
    return v->id = id;
  return -1;
}

void afficher_variable(const Variable* v){
  if (v==NULL)
    return;

  if (v->neg){
    printf(" NOT( x:%d ) ", v->id);
    return;
  }
  printf(" x:%d ", v->id);
}
