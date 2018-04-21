#include <stdio.h>
#include <stdlib.h>

#include "liresudoku.h"
#include "formules.h"
#include "to_dimacs.h"

//Convertit le fichier dimacs en Formule
static void read_dimacs(char *filename, Formule **f);

//Ecrit le fichier dimacs correspondant à la Formule f
static void write_dimacs(char *filename, Formule *f, int nb_var);

//Convertit le fichier sudoku en Formule
static void read_sudoku(char *filename, Formule **f);

//Ecrit le fichier sudoku correspondant à la Formule f
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
  Formule *f;
  read_dimacs(dimacs_file, &f);
  write_sudoku(sudoku_file, f,count_var_in_formule(f));
  free_formule(&f);
}

void sudoku_to_dimacs(char *dimacs_file, char *sudoku_file){
  Formule *f;
  read_sudoku(sudoku_file,&f);
  write_dimacs(dimacs_file,f,count_var_in_formule(f));
  free_formule(&f);
}

/* Fonctions locales */

//Convertit le fichier dimacs en formule
static void read_dimacs(char *filename, Formule **f){
  FILE *df = fopen(filename,"r");
  *f=NULL;
  if (df == NULL)
    return;

  //Lire chaque caractére du fichier dimacs pour le parser en formule
}

//Ecrit le fichier dimacs correspondant à la formule f (préalablement convertie en 3-sat)
static void write_dimacs(char *filename, Formule *f, int nb_var){
  FILE *df = fopen(filename,"w");
  Clause *c;
  //Entete du fichier dimacs
  fprintf(df,"p cnf %d %d\n", nb_var, count_clause_in_formule(f));
  //corps du fichier dimacs
  for(; f != NULL; f = f->next){
    for(c = f->c; c != NULL; c = c->next){
      if (c->v.neg)
	fprintf(df,"-");
      fprintf(df,"%d ",c->v.id);
    }
    fprintf(df,"0\n");
  }
  fclose(df);
}

//Convertit le fichier sudoku en formule 3-sat
static void read_sudoku(char *filename, Formule **f){
  FILE *df = fopen(filename,"w");
  sudoku s;
  Clause *clause = NULL;
  Variable v,v2;;
  int l,c,n;
  int i,j;
  int sqrt;
  readsudokufile(df,&s);
  sqrt = is_perfect_square(s.taille);
  //First part : Gen constraint 1 (Domain)
  v.neg = false;
  //Forall l
  for (l=0; l < s.taille; l++){
    v.l = l;
    //Forall c
    for (c=0; c < s.taille; c++){
      v.c = c;
      //Exists n
      for (n = 1; n <= s.taille; n++){
	v.n = n;
	v.id = coord_to_number(v.l,v.c,v.n, s.taille);
	push_var(&clause,v);
      }
      push_clause(f,clause);
      free_clause(&clause);
      clause = NULL;
    }
  }

  //Second part : Gen constraint 2 (Line unicity)
  for(l=0; i < s.taille; l++){
    v.l=l;
    for(c=0; c < s.taille; c++){
      v.c = c;
      for(n=1; n <= s.taille; n++){
	//First var x[l,c,n]
	v.n=n;
	v.neg = true;
	v.id = coord_to_number(v.l,v.c,v.n, s.taille);
	push_var(&clause,v);
	//Or loops for each column(imply)
	for(i=0; i <= c-1; i++){
	  v2 = (Variable){.l = v.l, .c = i, .n = v.n, .neg = true};
	  v2.id = coord_to_number(v2.l,v2.c, v2.n, s.taille);
	  push_var(&clause,v2);
	}
	for(i=c+1; i <= s.taille; i++){
	  v2 = (Variable){.l = v.l, .c = i, .n = v.n, .neg = true};
	  v2.id = coord_to_number(v2.l,v2.c, v2.n, s.taille);
	  push_var(&clause,v2);
	}
	push_clause(f,clause);
	free_clause(&clause);
	clause = NULL;
      }
    }
  }

  //Third part  : Gen constraint 3 (Column unicity)
  
  for(l=0; i < s.taille; i++){
    v.l=l;
    for(c=0; c < s.taille; c++){
      v.c = c;
      for(n=1; n <= s.taille; n++){
	//First var x[l,c,n]
	v.n=n;
	v.neg = true;
	v.id = coord_to_number(v.l,v.c,v.n, s.taille);
	push_var(&clause,v);
	//Or loops for each line(imply)
	for(i=0; i <= l-1; i++){
	  v2 = (Variable){.l = i, .c = v.c, .n = v.n, .neg = true};
	  v2.id = coord_to_number(v2.l,v2.c, v2.n, s.taille);
	  push_var(&clause,v2);
	}
	for(i=l+1; i <= s.taille; i++){
	  v2 = (Variable){.l = i, .c = v.c, .n = v.n, .neg = true};
	  v2.id = coord_to_number(v2.l,v2.c, v2.n, s.taille);
	  push_var(&clause,v2);
	}
	push_clause(f,clause);
	free_clause(&clause);
	clause = NULL;
      }
    }
  }
  //Fourth part : Gen constraint 4 (Square unicity)

  /* A ce point du code je me pose des questions sur à peu près tout, peut être faut-il mieux partir élever des
     chèvres dans le vercors qui sait ? */
  v.neg = v2.neg = true;
  for (n = 1 ; n <= s.taille; n++){
    v.n= v2.n = n;
    for (l = 0; l < sqrt-1;l++){
      v2.l = l*sqrt;
      for (c = 0; c < sqrt-1;c++){
	v2.c = c*sqrt;
	v2.id = coord_to_number(v2.l,v2.c,v2.n,s.taille);
	
	for(i = 1; i <= sqrt-1;i++){
	  v.c =c*sqrt+ i;
	  v.id = coord_to_number(v.l,v.c,v.n,s.taille);
	  push_var(&clause,v);
	  push_var(&clause,v2);
	}
	push_clause(f,clause);
	free_clause(&clause);
	
	v.c = c*sqrt;
	v.l = l*sqrt;
	for(i = 1; i <= sqrt-1;i++){
	  v.l = l*sqrt + i;
	  v.id = coord_to_number(v.l,v.c,v.n,s.taille);
	  push_var(&clause,v);
	  push_var(&clause,v2);
	}

	push_clause(f,clause);
	free_clause(&clause);

	v.c = c*sqrt;
	v.l = l*sqrt;
	
	for(i=1; i <= sqrt-1; i++){
	  v.l = l*sqrt+i;
	  for(j=1; j <= sqrt-1; j++){
	    v.c = c*sqrt+j;
	    v.id = coord_to_number(v.l,v.c,v.n,s.taille);
	    push_var(&clause,v);
	    push_var(&clause,v2);
	  }
	}
	push_clause(f,clause);
	free_clause(&clause);
      }
    }
  }

  /* A ce point ci je me demande quel est le pourcentage de code que j'aurais du vous laisser faire*/
  
  //Fifth part  : Gen sudoku corresponding clauses
  for (l=0; l < s.taille; l++){
    v.l = l;
    for (c=0; c < s.taille; c++){
      v.c = c;
      //Si on a une case remplie
      if (s.grille[l][c] != 0){
	v.n = s.grille[l][c];
	v.id = coord_to_number(v.l,v.c,v.n,s.taille);
	//La mettre en clause
	push_var(&clause,v);
	push_clause(f,clause);
	free_clause(&clause);
      }
    }
  }
  to_3sat(f);
  /* Et maintenant je me dis que c'est enfin fini pour cette fonction sauf que j'y ai fait aucun test, zero, nada
     et qu'elle ne compile surement pas*/
  /* Et la maintenant que j'ai fait une simili-optimisation du code je me met à me dire que ça va tout péter*/
}

//Ecrit le fichier sudoku correspondant à la formule f
static void write_sudoku(char *filename, Formule *f, int sudoku_size){
  FILE *df = fopen(filename,"w");
  fclose(df);
  f = NULL;
  sudoku_size = 0;
}
