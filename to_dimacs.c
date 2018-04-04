#include <stdio.h>
#include <stdlib.h>

#include "formules.h"
#include "to_dimacs.h"

//Convertit le fichier dimacs en formule
static void read_dimacs(char *filename, formule *f);

//Ecrit le fichier dimacs correspondant à la formule f
static void write_dimacs(char *filename, formule *f, int sudoku_size);

//Convertit le fichier sudoku en formule
static void read_sudoku(char *filename, formule *f, int sudoku_size);

//Ecrit le fichier sudoku correspondant à la formule f
static void write_sudoku(char *filename, formule *f, int sudoku_size);

//Convertit une coordonée (l,c,n) en un nombre entier, selon la taille du sudoku
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
  formule *f = creer_formule();
  read_dimacs(dimacs_file, f);
  write_sudoku(sudoku_file, f);
  liberer_formule(f);
}

void sudoku_to_dimacs(char *dimacs_file, char *sudoku_file){
  formule *f = creer_formule();
  read_sudoku(sudoku_file,f);
  write_dimacs(dimacs_file,f);
  liberer_formule(f);
}

/* Fonctions locales */

//Convertit le fichier dimacs en formule
static void read_dimacs(char *filename, formule *f){
  FILE *df = fopen(f,"r");
  if (df == NULL)
    return;

  //Lire chaque caractère du fichier dimacs pour le parser en formule
}

//Ecrit le fichier dimacs correspondant à la formule f
static void write_dimacs(char *filename, formule *f, int sudoku_size){
  FILE *df = fopen(f,"w");
}

//Convertit le fichier sudoku en formule
static void read_sudoku(char *filename, formule *f);

//Ecrit le fichier sudoku correspondant à la formule f
static void write_sudoku(char *filename, formule *f);
