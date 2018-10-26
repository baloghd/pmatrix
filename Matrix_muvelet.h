#ifndef MATRIX_MUV
#define MATRIX_MUV

#include "Matrix.h"

void sorszoroz(double *sor, int meret, double mivel);

void sorosszead(double *sor1, double *sor2, int meret);

void Matrix_sorcsere_helyben(Matrix *m, int egyiksor, int masiksor);

void Matrix_oszlopcsere_helyben(Matrix *m, int egyikoszlop, int masikoszlop);

void Matrix_Gauss(Matrix m);

Matrix Matrix_osszead(Matrix m1, Matrix m2);

Matrix Matrix_szorzas(Matrix jobb, Matrix bal);

#endif MATRIX_MUV