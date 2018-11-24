#ifndef MATRIX_IO
#define MATRIX_IO

#include <string.h>

#include "Matrix.h"

typedef enum Matrix_FAJLFORMATUM {
	MATRIX_FF_EGYSORBAN,
	MATRIX_FF_SORONKENT
} Matrix_FAJLFORMATUM;

void Matrix_kiir(Matrix m);

void Matrix_kiir_Octave(Matrix m);

Matrix *Matrix_sztringbol_strtok(const char *sz, int n_sor, int n_oszlop);

Matrix *Matrix_fajlbol_olvas(char *fajlnev);

void _fejlec_feldolgoz(char *fejlec,
					  int *sor,
					  int *oszlop,
					  Matrix_FAJLFORMATUM *formatum);  
					  
void Matrix_fajlba_ir(Matrix *m, FILE *fp);
#endif

