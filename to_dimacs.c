#include <stdio.h>
#include <stdlib.h>

#include "liresudoku.h"
#include "formules.h"
#include "to_dimacs.h"

//Convertit le fichier dimacs en sudoku
static void read_dimacs(char *filename,unsigned  int sudoku_size, sudoku *a);

//Ecrit le fichier dimacs correspondant à la Formule f
static void write_dimacs(char *filename, Formule *f);

//Convertit le fichier sudoku en Formule
static void read_sudoku(char *filename, Formule **f);

//Ecrit le fichier sudoku correspondant au sudoku a
static void write_sudoku(char *filename,sudoku *a);

//Convertit une coordonÃ©e (l,c,n) en un nombre entier, selon la taille du sudoku
unsigned int coord_to_number(unsigned int l, unsigned int c, unsigned int n, unsigned int sudoku_size){
  //Le sudoku size +1 permet d'eviter des doublets non liants
  //Les indices commencent à 1
  return n + c*(MAX+1) + l*(MAX+1)*(MAX+1);
}

//Convertit un nombre en (l,c,n) selon la taille du sudoku;
int number_to_coord(unsigned int number, unsigned int *l, unsigned int *c, unsigned int *n, unsigned int sudoku_size){
  *n = number % (MAX+1);
  number -= *n;

  *c = (number % ((MAX+1)*(MAX+1)))/(MAX+1);
  number -= (*c)*(MAX+1);

  *l = number/((MAX+1)*(MAX+1));

  return (*n) + (*c)*(MAX+1) + (*l)*(MAX+1)*(MAX+1);
}

void dimacs_to_sudoku(char *dimacs_file, char *sudoku_file,unsigned int sudoku_size){
  sudoku a;
  read_dimacs(dimacs_file,sudoku_size,&a);
  write_sudoku(sudoku_file,&a);
}

void sudoku_to_dimacs(char *dimacs_file, char *sudoku_file){
  Formule *f = NULL;
  read_sudoku(sudoku_file,&f);
  write_dimacs(dimacs_file,f);
  free_formule(&f);
}

/* Fonctions locales */

//Convertit le fichier dimacs en tableau sudoku
static void read_dimacs(char *filename,unsigned  int sudoku_size, sudoku *a){
  int id;
  unsigned int l,n,c;
  char Sat;
  a->taille = sudoku_size;
  FILE *df = fopen(filename,"r");
  if (df == NULL)
    return;
  fscanf(df," %c",&Sat);
  printf("%c",Sat);
  fscanf(df," %c",&Sat);
  printf("%c",Sat);
  fscanf(df," %c",&Sat);
  printf("%c",Sat);
  do{
    fscanf(df," %d",&id);
    if ( id > 0 && (unsigned ) id < coord_to_number(sudoku_size-1,sudoku_size-1,sudoku_size,0)){
      printf("ID OK : %d\n",id);
      if (number_to_coord((unsigned int) id,&l,&c,&n,a->taille) != id)
	puts("Probleme avec cet id");
      a->grille[l][c]=n;
    }
  }while (!feof(df));
}
//Ecrit le fichier dimacs correspondant à la formule f (préalablement convertie en 3-sat)
static void write_dimacs(char *filename, Formule *f){
  FILE *df = fopen(filename,"w");
  Clause *c;
  //Entete du fichier dimacs
  fprintf(df,"p cnf %d %d\n", count_var_in_formule(f), count_clauses_in_formule(f));
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
  FILE *df = fopen(filename,"r");
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
  for(l=0; l < s.taille; l++){
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
	for(i=c+1; i < s.taille; i++){
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
  
  for(l=0; l< s.taille; l++){
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
	for(i=l+1; i < s.taille; i++){
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
  for (l = 0; l <= sqrt-1;l++){
    v2.l = l*sqrt;
    for (c = 0; c <= sqrt-1;c++){
      v2.c = c*sqrt;
      for (n = 1 ; n <= s.taille; n++){
	v2.n = n;
	v2.id = coord_to_number(v2.l,v2.c,v2.n,s.taille);

	// Var temp
	v.n= n;
	v.l= l*sqrt;
	v.c= c*sqrt;
	for(i = 1; i <= sqrt-1;i++){
	  v.c =c*sqrt+ i;
	  v.id = coord_to_number(v.l,v.c,v.n,s.taille);
	  push_var(&clause,v);
	  push_var(&clause,v2);
	  push_clause(f,clause);
	  free_clause(&clause);
	}

	v.l= l*sqrt;
	v.c= c*sqrt;
	for(i = 1; i <= sqrt-1;i++){
	  v.l = l*sqrt + i;
	  v.id = coord_to_number(v.l,v.c,v.n,s.taille);
	  push_var(&clause,v);
	  push_var(&clause,v2);
	  push_clause(f,clause);
	  free_clause(&clause);
	}

	v.l= l*sqrt;
	v.c= c*sqrt;
	for(i=1; i <= sqrt-1; i++){
	  v.l = l*sqrt+i;
	  for(j=1; j <= sqrt-1; j++){
	    v.c = c*sqrt+j;
	    v.id = coord_to_number(v.l,v.c,v.n,s.taille);
	    push_var(&clause,v);
	    push_var(&clause,v2);
	    push_clause(f,clause);
	    free_clause(&clause);
	  }
	}
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
  //to_3sat(f );
  /* Et maintenant je me dis que c'est enfin fini pour cette fonction sauf que j'y ai fait aucun test, zero, nada
     et qu'elle ne compile surement pas*/
  /* Et la maintenant que j'ai fait une simili-optimisation du code je me met à me dire que ça va tout péter*/
}


//Ecrit le fichier sudoku correspondant aux sudoku dans un fichier
static void write_sudoku(char *filename,sudoku *a){
  FILE *df = fopen(filename,"w");
  int i,j;
  fprintf(df,"taille : %d * %d \n",a->taille,a->taille);  //affichage taille
  for (i=0;i<a->taille;i++){
    for(j=0;j<a->taille;j++){
      fprintf(df,"%3d |",a->grille[i][j]); //affichage valeur sur 3chiffres
    }
    fprintf(df,"\n");
    for(j=0;j<a->taille;j++){
      fprintf(df,"-----"); // presentation
    }
    fprintf (df,"\n");
  }
}
