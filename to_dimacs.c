#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

//Convertit une coordonÃ©e (l,c,n) en un nombre entier
unsigned int coord_to_number(unsigned int l, unsigned int c, unsigned int n){
  //Le sudoku size +1 permet d'eviter des doublets non liants
  //Les indices commencent à 1
  return n + c*(MAX+1) + l*(MAX+1)*(MAX+1);
}

//Convertit un nombre en (l,c,n)
//Les pointeurs sont des références
int number_to_coord(unsigned int number, unsigned int *l, unsigned int *c, unsigned int *n){

  //On affecte à n la valeur qui suit
  *n = number % (MAX+1);
  number -= *n;

  *c = (number % ((MAX+1)*(MAX+1)))/(MAX+1);
  number -= (*c)*(MAX+1);

  *l = number/((MAX+1)*(MAX+1));

  //On renvoit le nouvel id calculé qui doit être égal à l'ancien (number) sinon c'est que y'a un souci
  return (*n) + (*c)*(MAX+1) + (*l)*(MAX+1)*(MAX+1);
}

void dimacs_to_sudoku(char *dimacs_file, char *sudoku_file,unsigned int sudoku_size){
  sudoku a;
  //On affecte à a la présente dans le fichier dimacs
  read_dimacs(dimacs_file,sudoku_size,&a);
  //On l'écrit dans le fichier sudoku
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
  char sat[4];
  const unsigned int high_value = coord_to_number(sudoku_size-1,sudoku_size-1,sudoku_size) + 1;
  FILE *df = fopen(filename,"r");
  a->taille = sudoku_size;
  if (df == NULL)
    return;
  //Lecture de l'entete et affichage
  fgets(sat,3,df);
  if (!(sat[0] == 'S' && sat[1] == 'A' && sat[2] == 'T')){
    puts("unsastifiable dimacs file, no sudoku");
    fclose(df);
    return;
  }

  //Lecture des variables
  do{
    fscanf(df," %d",&id);
    //Si id est positif => on a une valeur à donner à la case
    //Si id > coord_machin => C'est une fausse valeur générée par le to_3sat donc on la saute
    if ( id > 0 && (unsigned ) id < high_value){
      printf("ID OK : %d\n",id);
      number_to_coord((unsigned) id, &l,&c,&n);
      //On affecte la bonne valeur à la case dans le sudoku
      a->grille[l][c]=n;
    }
    //Tant que le fichier est pas fini
  }while (!feof(df));
  fclose(df);
}
//Ecrit le fichier dimacs correspondant à la formule f (préalablement convertie en 3-sat)
static void write_dimacs(char *filename, Formule *f){
  FILE *df = fopen(filename,"w");
  Clause *c = NULL;
  //Entete du fichier dimacs
  fprintf(df,"p cnf %d %d\n", count_var_in_formule(f), count_clauses_in_formule(f));
  //corps du fichier dimacs
  //Pour chaque clause de la formule
  for(; f != NULL; f = f->next){
    //Pour chaque variable de clause
    for(c = f->c; c != NULL; c = c->next){
      //Si elle est en négation on écrit le "-" cf doc dimacs
      if (c->v.neg)
	fprintf(df,"-");
      //Puis on écrit le numéro dimacs de la var
      fprintf(df,"%d ",c->v.id);
    }
    //On finit la ligne (cf doc dimacs)
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
  assert(f != NULL);
  //On récupére dans s toutes les valeurs du fichier sudoku
  readsudokufile(df,&s);
  fclose(df);
  //sqrt <- racine(s.taille) si s.taille est un carré, sinon -1
  sqrt = is_perfect_square(s.taille);
  //SI on choppe un -1 c'est que on a un bleme on se casse
  if (sqrt < 0)
    return;
  
  //Generation de la constraint 1 (Domaine)
  //On affecte à v et v2 les valeurs par défaut nul (Tout à 0, et variable non neg)
  v = v2 = (Variable){.id = 0,.l = 0,.c = 0,.n = 0, .neg = false};
  puts("Step 1");
  //Pour tout l dans [0,s.taille[
  for (l=0; l < s.taille; l++){
    v.l = l;
    //Forall c
    for (c=0; c < s.taille; c++){
      v.c = c;
      //Exists n
      assert(clause == NULL);
      for (n = 1; n <= s.taille; n++){
	//On crée la variable x[l,c,n]
	v.n = n;
	v.id = coord_to_number(v.l,v.c,v.n);
	//On l'ajoute à la clause courzante (si vide elle est créée)
	push_var(&clause,v);
      }
      //On ajoute la clause à l'ensemble de toutes les formules
      push_clause(f,clause);
      //On détruit la clausse
      free_clause(&clause);
     
    }
  }
  //Gen constraint 2 (Line unicity)
  puts("Step 2");
  v = v2 = (Variable){.id = 0,.l = 0,.c = 0,.n = 0};
  for(l=0; l < s.taille; l++){
    v.l=l;
    for(c=0; c < s.taille; c++){
      v.c = c;
      for(n=1; n <= s.taille; n++){
	//First var x[l,c,n]
	v.n=n;
	v.neg = true;
	v.id = coord_to_number(v.l,v.c,v.n);
	assert(clause == NULL);
	//Or loops for each column
	for(i=0; i <= c-1; i++){
	  push_var(&clause,v);
	  v2 = (Variable){.l = v.l, .c = i, .n = v.n, .neg = true};
	  v2.id = coord_to_number(v2.l,v2.c, v2.n);
	  push_var(&clause,v2);
	  push_clause(f,clause);
	  free_clause(&clause);
	    
	}
	assert(clause == NULL);
	for(i=c+1; i < s.taille; i++){
	  push_var(&clause,v);
	  v2 = (Variable){.l = v.l, .c = i, .n = v.n, .neg = true};
	  v2.id = coord_to_number(v2.l,v2.c, v2.n);
	  push_var(&clause,v2);
	  push_clause(f,clause);
	  free_clause(&clause);
	}
      }
    }
  }

  //Gen constraint 3 (Column unicity)
  puts("Step 3 !");
  v = v2 = (Variable){.id = 0,.l = 0,.c = 0,.n = 0};
  v.neg = true;
  for(l=0; l< s.taille; l++){
    v.l=l;
    for(c=0; c < s.taille; c++){
      v.c = c;
      for(n=1; n <= s.taille; n++){
	//First var x[l,c,n]
	v.n=n;
	v.id = coord_to_number(v.l,v.c,v.n);
	assert(clause == NULL);
	//Or loops for each line(imply)
	for(i=0; i <= l-1; i++){
	  push_var(&clause,v);
	  v2 = (Variable){.l = i, .c = v.c, .n = v.n, .neg = true};
	  v2.id = coord_to_number(v2.l,v2.c, v2.n);
	  push_var(&clause,v2);
	  push_clause(f,clause);
	  free_clause(&clause);
	}
	for(i=l+1; i < s.taille; i++){
	  push_var(&clause,v);
	  v2 = (Variable){.l = i, .c = v.c, .n = v.n, .neg = true};
	  v2.id = coord_to_number(v2.l,v2.c, v2.n);
	  push_var(&clause,v2);
	  push_clause(f,clause);
	  free_clause(&clause);
	}
      }
    }
  }

  //Gen constraint 4 (Square unicity)

  puts("Step 4 !!!!");
  v = v2 = (Variable){.id = 0,.l = 0,.c = 0,.n = 0,.neg=false};
  v.neg = v2.neg = true;
  for (l = 0; l <= sqrt-1;l++){
    v2.l = l*sqrt;
    v.l= l*sqrt;
    for (c = 0; c <= sqrt-1;c++){
      v2.c = c*sqrt;
      v.c= c*sqrt;
      for (n = 1 ; n <= s.taille; n++){
	v2.n = n;
	v2.id = coord_to_number(v2.l,v2.c,v2.n);
	// Var temp
	v.n= n;
	 assert(clause == NULL);
	for(i = 1; i <= sqrt-1;i++){
	  v.c =c*sqrt+ i;
	  v.id = coord_to_number(v.l,v.c,v.n);
	  push_var(&clause,v);
	  push_var(&clause,v2);
	  push_clause(f,clause);
	  free_clause(&clause);
	}

	v.l= l*sqrt;
	v.c= c*sqrt;
	 assert(clause == NULL);
	for(i = 1; i <= sqrt-1;i++){
	  v.l = l*sqrt + i;
	  v.id = coord_to_number(v.l,v.c,v.n);
	  push_var(&clause,v);
	  push_var(&clause,v2);
	  push_clause(f,clause);
	  free_clause(&clause);
	}

	v.l= l*sqrt;
	v.c= c*sqrt;
	 assert(clause == NULL);
	for(i=1; i <= sqrt-1; i++){
	  v.l = l*sqrt+i;
	  for(j=1; j <= sqrt-1; j++){
	    v.c = c*sqrt+j;
	    v.id = coord_to_number(v.l,v.c,v.n);
	    push_var(&clause,v);
	    push_var(&clause,v2);
	    push_clause(f,clause);
	    free_clause(&clause);
	  }
	}
      }
    }
  }
  puts("Step 5");
  v.neg = false;
  //Fifth part  : Gen sudoku corresponding clauses
  for (l=0; l < s.taille; l++){
    v.l = l;
    for (c=0; c < s.taille; c++){
      v.c = c;
      //Si on a une case remplie
      if (s.grille[l][c] != 0){
	v.n = s.grille[l][c];
	v.id = coord_to_number(v.l,v.c,v.n);
	assert(clause == NULL);
	//La mettre en clause
	push_var(&clause,v);
	push_clause(f,clause);
	free_clause(&clause);
      }
    }
  }
  //Transfo en 3sat
  puts("Final gen step -> To 3 sat");
  to_3sat(f );
}


//Ecrit le fichier sudoku correspondant aux sudoku dans un fichier
static void write_sudoku(char *filename,sudoku *a){
  FILE *df = fopen(filename,"w");
  int i,j;
  assert(a != NULL);
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
  fclose(df);
}
