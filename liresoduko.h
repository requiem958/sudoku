
#define MAX 16

typedef struct { 
int taille;
int grille [MAX][MAX];
} soduko ;

void readsodukofile (FILE *f,soduko *a);
// prend un fichier f ouvert en mode lecture 
// et un soduko a et rempli le soduko a avec le fichier f
// exemple de fichier
//4
// 6 1 0 3
// 5 0 3 4
// 0 3 4 5
// 0 9 8 7

void affichergrille (soduko a);