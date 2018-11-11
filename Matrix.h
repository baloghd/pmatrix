#ifndef MATRIX_ALAP
#define MATRIX_ALAP

#include <stdbool.h>

typedef struct Matrix
{
    int sor, oszlop;
    double **tomb;
} Matrix;

//a Matrix ertekeket tarolo tombjenek dinamikus helyfoglalasa
bool Matrix_memfoglal(Matrix *m);
//a Matrix ertekeket tarolo tombjet tartolo dinamikusan foglalt memoria felszabaditasa
void Matrix_memfelszab(Matrix *m);

Matrix Matrix_inic(int sor, int oszlop);

Matrix Matrix_identitas(int sor);


#endif
