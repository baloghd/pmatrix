#ifndef MATRIX_IO
#define MATRIX_IO

#include <string.h>

#include "Matrix.h"

void Matrix_kiir(Matrix m);

void Matrix_kiir_Octave(Matrix m);

int match(const char *s, const char *p, int overlap);

Matrix Matrix_sztringbol(char *sz);

Matrix Matrix_sztringbol_strtok(const char *sz);

Matrix Matrix_fajlbol_olvas(FILE *fp);

#endif

