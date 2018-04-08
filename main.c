#include <stdio.h>
#include <stdlib.h>

#define TEST_CLAUSES

#ifdef TEST_NUMBCOORD

#include "to_dimacs.h"

#endif

#ifdef TEST_CLAUSES

#include "clauses.h"

#endif

#ifdef TEST_VAR

#include "formules.h"

#endif

int main(void){
  #ifdef TEST_CLAUSES
  Clause *c = NULL;
  Variable v = {0,0,0,0,false};

  printf("%d\n",length(c));
  for (v.id = 0; v.id < 4;v.id++){
    printf("pu : %d ",push_var(&c,v));
    printf("le : %d\n",length(c));
  }
  v.id = 3;
  printf("pu : %d",push_var(&c,v));
  printf("le : %d\n",length(c));

  printf("Valid %d\n", is_valid(c));
  v.id = 70;
  v.neg = !v.neg;
  push_var(&c,v);
  printf("Valid after not(70) but no 70  %d\n", is_valid(c));
  
  printf("Valid %d\n", is_valid(c));
  v.neg = !v.neg;
  push_var(&c,v);
  printf("Valid after not(70) and 70 %d (Must be 1)\n" , is_valid(c));

  printf("le : %d\n",length(c));
  c = del_var(&c,v);
  printf("le : %d (Must be preced line -1)\n",length(c));

  while(c->next != NULL){
    printf("pop : %d\n",pop_var(&c,&v));
    printf("var : %d\n",v.id);
    printf("le : %d\n",length(c));
  }
  pop_var(&c,&v);
  pop_var(&c,&v);

  printf("le : %d\n",length(c));
  for (v.id = 0; v.id < 4;v.id++)
    push_var(&c,v);
  printf("le : %d\n",length(c));
  free_clause(&c);
  printf("le : %d\n",length(c));
  return 0;
  #endif
  #ifdef TEST_NUMBCOORD
#define SUDOKU_SIZE 9
  int l=0,c=0,n=1;
  int number=0;

  //Test pour le sudoku à 1 case
  number = coord_to_number(l,c,n,1);
  printf("(%d,%d,%d) -> %d\n",l,c,n,number);
  l = c = n = 0;
  number_to_coord(number,&l,&c,&n,1);
  printf("(%d,%d,%d) <- %d\n",l,c,n,number);

  printf("Sudoku à %d cases, %d valeurs par cases", SUDOKU_SIZE, SUDOKU_SIZE);
  //Test total du sudoku à 4 cases
  for (l=0; l < SUDOKU_SIZE; l++){
    printf("Ligne %d\n",l);
    for (c=0; c < SUDOKU_SIZE; c++){
      printf("\tColonne %d\n",c);
      for (n=1; n <= SUDOKU_SIZE; n++){
	number = coord_to_number(l,c,n,SUDOKU_SIZE);
	printf("\t\tValeur %d\n",n);
	printf("\t\t\tLe tout codé par : %d\n",number);
      }
    }
  }
  if (number != SUDOKU_SIZE*SUDOKU_SIZE*SUDOKU_SIZE-1)
    puts("Il manque des valeurs");
  
  return 0;
  #endif
  #ifdef TEST_VAR
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
  #endif
}
