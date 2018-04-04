#include <stdio.h>
#include <stdlib.h>

#include "formules.h"
#include "to_dimacs.h"

#define TEST_VAR

int main(void){
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
