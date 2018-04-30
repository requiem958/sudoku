#include <stdio.h>
#include <stdlib.h>

#define TEST_SUDOKU

#ifdef TEST_NUMBCOORD

#include "types.h"
#include "clauses.h"
#include "formules.h"
#include "to_dimacs.h"

#endif

#ifdef TEST_CLAUSES

#include "types.h"
#include "clauses.h"

#endif

#ifdef TEST_FORM

#include "types.h"
#include "clauses.h"
#include "formules.h"
#include "liresudoku.h"
#include "to_dimacs.h"

#endif

#ifdef TEST_SUDOKU

#include "types.h"
#include "clauses.h"
#include "formules.h"
#include "liresudoku.h"
#include "to_dimacs.h"
#endif

int main(void){
#ifdef TEST_CLAUSES
  Clause *c = NULL;
  Clause *c2 = NULL;
  Variable v = {0,0,0,0,false};

  //Null clause length test
  printf("%d\n",length(c));

  //push_clause test
  for (v.id = 0; v.id < 4;v.id++){
    printf("pu : %d (Must be 0)",push_var(&c,v));
    printf("le : %d (Must be %d)\n",length(c),v.id+1);
  }
  //
  printf("Equals ? %d Must be 1\n", equal_clause(c,c));
  push_var(&c2,(Variable){-1,0,0,0,false});
  push_var(&c2,(Variable){10,0,0,0,false});
  push_var(&c2,(Variable){8,0,0,0,false});
  printf("Equals ? %d Must be 0\n", equal_clause(c,c2));
  getchar();
  //Print clause
  print_clause(c);
  //push_clause with something already present
  v.id = 3;
  printf("pu : %d (Must be 1)",push_var(&c,v));
  printf("le : %d (Must be 401)\n",length(c));

  //Validity of an unvalid clause
  printf("Valid %d (Must be 0\n", is_valid(c));
  v.id = 70;
  v.neg = !v.neg;
  push_var(&c,v);
  printf("Valid after not(70) but no 70  %d (Must be 0)\n", is_valid(c));

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
#define SUDOKU_SIZE 4
  unsigned int l=0,c=1,n=2;
  int number=0;

  //Test pour le sudoku � 4 case
  number = coord_to_number(l,c,n,SUDOKU_SIZE);
  printf("(%d,%d,%d) -> %d\n",l,c,n,number);
  l = c = n = 0;
  number_to_coord(number,&l,&c,&n,SUDOKU_SIZE);
  printf("(%d,%d,%d) <- %d\n",l,c,n,number);

  printf("Sudoku à %d cases, %d valeurs par cases", SUDOKU_SIZE, SUDOKU_SIZE);
  //Test total du sudoku à 4 cases
  for (l=0; l < SUDOKU_SIZE; l++){
    for (c=0; c < SUDOKU_SIZE; c++){
      for (n=1; n <= SUDOKU_SIZE; n++){
	number = coord_to_number(l,c,n,SUDOKU_SIZE);
	printf("[l:%d,c:%d,n:%d] -> %d\n",l,c,n,number);
      }
    }
  }
  
  return 0;
#endif
#ifdef TEST_FORM

  Clause * c = NULL;
  Variable v;
  Formule * f4 = NULL;

  /* Test new_formule : retourne une formule vide */
  /* Cas : initialisà*/
  Formule f1 = new_formule();

  /* Cas : initialisé avec NULL */
  Formule * f2 = NULL;

  /* Cas : non initialisé */
  Formule f3;  

  /* Test is_empty_formule : retourne un booléen */

  /* Résultat attendu : 0 */
  printf("%i\n",is_empty_formule(&f1));

  /* Résultat attendu : 1 */
  printf("%i\n",is_empty_formule(f2));

  /* Résultat attendu : 0 */
  printf("%i\n",is_empty_formule(&f3));

  for(v.id = 0; v.id < 5; v.id++)
    push_var(&c,v);

  /* Test count_var_in_formule : retourne un entier */
  /* Résultat attendu : 4 */

  /* Test count_clauses_in_formule : retourne un entier */
  /* Résultat attendu : 1 */ 
  push_clause(&f4,c);
  v.id = 72;
  push_var(&c,v);
  push_clause(&f4,c);
  printf("nombre de var = %i\n",count_var_in_formule(f4));
  printf("nombre de clauses = %i\n\n",count_clauses_in_formule(f4));
  print_formule(f4);
  to_3sat(&f4);
  print_formule(f4);
  free_clause(&c);

  /* Test new_clause : retourne une clause vide */

  Variable v1;

  Clause * c2 = NULL;
  /* Test length : retourne un entier */
  

  for(v1.id = 0; v1.id < 4; v1.id++)
    push_var(&c2,v1);
  push_var(&c2,v1);

  printf("Clause c2 , taile (%i) : \n",length(c2));
  print_clause(c2);
  printf("\n");

  /* Test copy_clause : retounre une clause */
  Clause * c3 = NULL;

  c3 = clause_copy(c2);
	
  printf("Clause c3 , taille(%i) : \n",length(c3));
  print_clause(c3);
  printf("\n");

  /* Test pop_var : retourne un entier */
  /* Résultat attendu : 0  */ 
  /* printf("Clause c3, on retire la dernière variable  : %i \n\n",pop_var(c3,&v1)); */

  /* Test del_var : retroune une clause moins la variable donnée */
  /* c3 = del_var(&c3,v1); */

  /* Test equal_clause : retourne un booléen */
  /* Résultat attendu sans del_var(&c3,v1) : true */
  /* Résultat attendu avec del_var(&c3,v1) : false */
  bool res = equal_clause(c2,c3);
  if ( res == true ) printf("c2 et c3 sont égales \n\n");
  else 		     printf("c2 et c3 ne sont pas égales \n\n");


  /* Test is_valid : retourne un booléen */
  Variable v2;	
  Clause * c4 = NULL;

  v2.id = 0;
  push_var(&c4,v2);
	
  v2.neg = false;
  push_var(&c4,v2);

  print_clause(c4);

  /* Résultat attendu pour c4 : true */
  bool res1 = is_valid(c4);
  if ( res1 == true ) printf("c4 est valide\n\n");
  else 		      printf("c4 n'est pas valide \n\n");

  /* Résultat attendu pour c3 : false */
  res1 = is_valid(c3);
  if ( res1 == true ) printf("c3 est valide\n\n");
  else 		      printf("c3 n'est pas valide \n\n");


  return 0;
#endif
#ifdef TEST_SUDOKU
  /* Test readsudokufile, affichergrille et writesudokufile */
  sudoku P;
  FILE * file1 = fopen("sudoku.txt","r");
  FILE * file2 = fopen("sudoku1.txt","w");
  readsudokufile(file1,&P);
  affichergrille(&P);
  writesudokufile(file2,&P);

  fclose(file1);
  fclose(file2);

  /* Test sudoku_to_dimacs */
  printf("Test final\n");
  sudoku_to_dimacs("dim.txt","sudoku.txt");
  system("./minisat dim.txt dim_sat.txt");
  dimacs_to_sudoku("dim_sat.txt","sudoku_sol.txt",4);
  return 0;
#endif
}
