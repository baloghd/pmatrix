#ifndef MATRIX_MUV
#define MATRIX_MUV

#include "Matrix.h"

double *sorszoroz(double *sor, int meret, double mivel);

void sorszoroz_helyben(double *sor, int meret, double mivel);

double *sorosszead(double *sor1, double *sor2, int meret);

void sorosszead_helyben(double *sor1, double *sor2, int meret);

double Matrix_nyom(Matrix *m);

int _van_meg_nemnulla_sor(Matrix m, int kezdosor);

void Matrix_sorcsere_helyben(Matrix *m, int egyiksor, int masiksor);

void Matrix_oszlopcsere_helyben(Matrix *m, int egyikoszlop, int masikoszlop);

void Matrix_Gauss(Matrix *m);

Matrix *Matrix_osszead(Matrix m1, Matrix m2);

Matrix *Matrix_szorzas(Matrix jobb, Matrix bal);

bool _nullasor(double *sor, int meret);

int Matrix_rang(const Matrix m);

#endif
