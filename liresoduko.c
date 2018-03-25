#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "soduko.h"

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
void readsudokufile (FILE *f,soduko *a){
	int dim,chi;
	int i,j;
	fscanf(f," %d",&dim);
	if (!(dim <17 && dim>0)){  // verification de la taille 
		printf ("erreur grille de dimension non comprise entre 0 et 16 ");
		return ;
	}
	if (is_perfect_square(dim) <= 0){
	  printf("Impossible de construire un sudoku qui n'est pas carré parfait");
	  return;
	}
	a->taille=dim;
	for (i=0;i<dim;i++){  // on complete la grille de soduko 
		for (j=0;j<dim;j++){
			fscanf(f," %d",&chi);
			if (chi < 0 || chi > dim){ //Sur un sudoku de taille N on a droit à une valeur entre 1 et N inclus pas juste 9 ;)
				printf ("la valeur contenue dans la case ( %d , %d  ) à une valeur invalide (%d )\n",i,j,chi);
			}
			a->grille[i][j]=chi;
		}
	}
}

void affichergrille (soduko a){
		int i,j;
		printf("taille : %d * %d \n",a.taille,a.taille);  //affichage taille
		for (i=0;i<a.taille;i++){
			for(j=0;j<4;j++){
				printf("%d |",a.grille[i][j]); //affichage valeur 
			}
			printf("\n");
			for(j=0;j<a.taille;j++){
				printf("---"); // presentation
			}
			printf ("\n");
	}	
}
