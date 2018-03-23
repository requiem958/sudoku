#include <stdio.h>
#include <stdlib.h>

#include "formules.h"

int main(void){
  formule *f=NULL;
  variable v;
  v.neg = FALSE;

  f = creer_formule();
  
  set_var_id (&v, 101);
  push_var(f,0,v);

  set_var_id(&v,99);
  push_var(f,0,v);

  set_var_id(&v,200);
  push_var(f,0,v);

  neg_var(&v);
  push_var(f,1,v);
  afficher_formule(f);

  liberer_formule(f);
  return 0;
}
