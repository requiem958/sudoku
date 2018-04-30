
#define MAX 16

typedef struct { 
int taille;
int grille [MAX][MAX];
} sudoku ;

void readsudokufile (FILE *f,sudoku *a);
// prend un fichier f ouvert en mode lecture 
// et un sudoku a et rempli le soduko a avec le fichier f
// exemple de fichier
//4
// 6 1 0 3
// 5 0 3 4
// 0 3 4 5
// 0 9 8 7

//Ecrit la grille a dans le ficher f
void writesudokufile(FILE*f, sudoku *a);

void affichergrille (sudoku* a);

//Local function to see if a is a perfect_square = a k*k, k in N
int is_perfect_square(int a);
