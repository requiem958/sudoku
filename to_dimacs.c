#include <stdio.h>
#include <stdlib.h>

#include "formules.h"
#include "to_dimacs.h"

//Convertit le fichier dimacs en Formule
static void read_dimacs(char *filename, Formule *f);

//Ecrit le fichier dimacs correspondant Ã  la Formule f
static void write_dimacs(char *filename, Formule *f, int sudoku_size);

//Convertit le fichier sudoku en Formule
static void read_sudoku(char *filename, Formule *f, int sudoku_size);

//Ecrit le fichier sudoku correspondant Ã  la Formule f
static void write_sudoku(char *filename, Formule *f, int sudoku_size);

//Convertit une coordonÃ©e (l,c,n) en un nombre entier, selon la taille du sudoku
unsigned int coord_to_number(unsigned int l, unsigned int c, unsigned int n, unsigned int sudoku_size){
  //Le n-1 permet d'assurer qu'on ai jamais deux fois la meme valeur
  return (n-1) + c*sudoku_size + l*sudoku_size*sudoku_size;
}

//Convertit un nombre en (l,c,n) selon la taille du sudoku;
int number_to_coord(unsigned int number, unsigned int *l, unsigned int *c, unsigned int *n, unsigned int sudoku_size){
  *n = 1 + number % sudoku_size;
  number -= (*n)-1;

  *c = (number % (sudoku_size*sudoku_size))/sudoku_size;
  number -= (*c)*sudoku_size;

  *l = number/(sudoku_size*sudoku_size);

  return (*n)-1 + (*c)*sudoku_size + (*l)*sudoku_size*sudoku_size;
}

void dimacs_to_sudoku(char *dimacs_file, char *sudoku_file){
  Formule *f = NULL;
  *f = new_formule();
  read_dimacs(dimacs_file, f);
  write_sudoku(sudoku_file, f,0);
  free_formule(&f);
}

void sudoku_to_dimacs(char *dimacs_file, char *sudoku_file){
  Formule *f =NULL;
  *f = new_formule();
  read_sudoku(sudoku_file,f,0);
  write_dimacs(dimacs_file,f,0);
  free_formule(&f);
}

/* Fonctions locales */

//Convertit le fichier dimacs en formule
static void read_dimacs(char *filename, Formule *f){
  FILE *df = fopen(filename,"r");
  f=NULL;
  if (df == NULL)
    return;

  //Lire chaque caractÃ¨re du fichier dimacs pour le parser en formule
}

//Ecrit le fichier dimacs correspondant Ã  la formule f
static void write_dimacs(char *filename, Formule *f, int sudoku_size){
  FILE *df = fopen(filename,"w");
  fclose(df);
  f = NULL;
  sudoku_size = 0;
}

//Convertit le fichier sudoku en formule
static void read_sudoku(char *filename, Formule *f, int* sudoku_size){
  FILE *df = fopen(filename,"w");
  sudoku s;
  Clause *c = NULL;
  Variable v;
  int i = 0, c = 0;
  readsudokufile(df,&s);

  //First part : Gen constraint 1 (Domain)
  v.neg = false;
  for (; i < s.taille; i++){
    v.l = i;
    for (; c < s.taile; c++){
      v.c = c;
      *c = new_clause();
      for (v.n = 1; v.n <= s.taille; v.n++){
	v.id = coord_to_number(v.l,v.c,v.n, s.taille);
	push_var(&c,v);
      }
      push_clause(&f,c);
    }
  }

  //Second part : Gen constraint 2 (Line unicity)

  //Third part  : Gen constraint 3 (Column unicity)

  //Fourth part : Gen constraint 4 (Square unicity)

  //Fifth part  : Gen sudoku corresponding clauses

  for (i=0; i < s.taille; i++){
    v.l = i;
    for (c=0; c < s.taille; c++){
      v.c = c;
      //Si on a une case remplie
      if (s.grille[i][c] != 0){
	*c = new_clause();
	v.n = s.grille[i][c];
	v.id = coord_to_number(v.l,v.c,v.n,s.taille);
	//La mettre en clause
	push_var(&c,v);
	push_clause(&f,c)
      }
    }
}

//Ecrit le fichier sudoku correspondant Ã  la formule f
static void write_sudoku(char *filename, Formule *f, int sudoku_size){
  FILE *df = fopen(filename,"w");
  fclose(df);
  f = NULL;
  sudoku_size = 0;
}
