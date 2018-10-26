#ifndef MATRIX_IO
#define MATRIX_IO

#include <string.h>

#include "Matrix.h"

void Matrix_kiir(Matrix m);

void Matrix_kiir_Octave(Matrix m);

Matrix Matrix_sztringbol(char *sz);

Matrix Matrix_sztringbol_strtok(char *sz);

Matrix Matrix_fajlbol(FILE *fp);

#endif MATRIX_IO