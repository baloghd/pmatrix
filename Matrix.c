#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

/** a Matrix struktúrának foglal helyet **/
bool Matrix_memfoglal(Matrix *m)
{
	
    m->tomb = (double **) malloc(m->sor * sizeof(double *));

    for (int i = 0; i < m->sor; ++i)
    {
        m->tomb[i] = (double *) malloc(m->oszlop * sizeof(double));
    }

    return m->tomb != NULL;
}

/** a Matrix struktúrának foglalt helyet szabadítja fel **/
void Matrix_memfelszab(Matrix *m)
{
    for (int i = 0; i < m->sor; ++i)
    {
        free(m->tomb[i]);
    }
    free(m->tomb);
}
/** a Matrixot inicializáló fgv **/
Matrix Matrix_inic(int sor, int oszlop)
{
    Matrix m;
    m.sor = sor;
    m.oszlop = oszlop;

    if (Matrix_memfoglal(&m))
    {
        return m;
    }
    else
    {
        printf("HIBA: nem sikerult memoriateruletet foglalni a matrixnak.");
        return (Matrix) {0, 0};
    }
}
/** a megadott méretű identitás-mátrixot visszaadó fgv **/
Matrix Matrix_egyseg(int sor)
{
    Matrix m = Matrix_inic(sor, sor);
    for (int i = 0; i < sor; ++i)
    {
        for (int j = 0; j < sor; ++j)
        {
             m.tomb[i][j] = (i == j) ? 1 : 0;
        }
    }
    return m;
}
