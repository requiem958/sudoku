#include <stdio.h>
#include <stdlib.h>
#include "liresudoku.h"

//Local function to see if a is a perfect_square = a k*k, k in N
int is_perfect_square(int a){
  int i = 0;

  while (i*i <= a){
    if (i*i == a)
      return i;
    else
      i++;
  }
  return -1;

}


void readsudokufile (FILE *f,sudoku *a){
  int dim,chi;
  int i,j;
  fscanf(f," %d",&dim);
  if (!(dim <MAX+1 && dim>0)){  // verification de la taille
    printf ("erreur grille de dimension non comprise entre 0 et %d ", MAX);
    return ;
  }
  if (is_perfect_square(dim) <= 0){
    printf("Impossible de construire un sudoku qui n'est pas carrÃ© parfait");
    return;
  }
  a->taille=dim;
  for (i=0;i<dim;i++){  // on complete la grille de soduko
    for (j=0;j<dim;j++){
      fscanf(f," %d",&chi);
      if (chi == 0){//On est sur une valeur à découvrir
	a->grille[i][j]=0;
      }
      else if (chi > dim){ //On empeche les valeurs supérieurs à la dim (on cosidère 0 a la place)
	printf ("la valeur contenue dans la case ( %d , %d  ) Ã  une valeur invalide (%d )\n",i,j,chi);
	a->grille[i][j]=0;
      }
      else //On est sur une valeur normale
	a->grille[i][j]=chi;
    }
  }
}

void affichergrille (sudoku* a){
  int i,j;
  printf("taille : %d * %d \n",a->taille,a->taille);  //affichage taille
  for (i=0;i<a->taille;i++){
    for(j=0;j<a->taille;j++){
      printf("%3d |",a->grille[i][j]); //affichage valeur sur 3chiffres
    }
    printf("\n");
    for(j=0;j<a->taille;j++){
      printf("---"); // presentation
    }
    printf ("\n");
  }
}
