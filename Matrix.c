#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "debugmalloc.h"

/*! \file */ 

/*! 
 *  \brief a Matrix struktúrának foglal helyet
 *  \param m a mátrixra mutató pointer
 * 	\return true, ha sikerült a memóriafoglalás; false, ha nem
 */
bool Matrix_memfoglal(Matrix *m)
{
    m->tomb = (double **) malloc(m->sor * sizeof(double *));

    for (int i = 0; i < m->sor; ++i)
    {
        m->tomb[i] = (double *) malloc(m->oszlop * sizeof(double));
    }

    return m->tomb != NULL;
}

/*!
 *  \brief a Matrix struktúrának foglalt helyet szabadítja fel
 *  \param m a felszabadítandó mátrix
 */
void Matrix_memfelszab(Matrix *m)
{
    for (int i = 0; i < m->sor; ++i)
    {
        free(m->tomb[i]);
    }
    free(m->tomb);
    free(m);
}
/*!
 *  \brief a Matrixot inicializáló függvény
 *  \param sor a sorok száma
 *  \param oszlop a oszlopok száma
 * 	\return az inicializált mátrixra mutató pointer
 */
Matrix *Matrix_inic(int sor, int oszlop)
{
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    m->sor = sor;
    m->oszlop = oszlop;

    if (Matrix_memfoglal(m))
    {
        return m;
    }
    else
    {
        printf("HIBA: nem sikerult memoriateruletet foglalni a matrixnak.");
        return m;
    }
}
/*!
 *  \brief a megadott méretű  egységmátrixot visszaadó függvény
 *  \param sor a sorok száma (= oszlopok száma, négyzetes mátrix)
 * 	\return az inicializált mátrixra mutató pointer
 */
Matrix *Matrix_egyseg(int sor)
{
    Matrix *m = Matrix_inic(sor, sor);
    for (int i = 0; i < sor; ++i)
    {
        for (int j = 0; j < sor; ++j)
        {
             m->tomb[i][j] = (i == j) ? 1 : 0;
        }
    }
    return m;
}
/*!
 *  \brief mátrixot másol egy újonnan lefoglalt helyre
 *  \param mit a másolandó mátrixra mutató pointer
 * 	\return a másolt mátrixra mutató pointer
 */
Matrix *Matrix_masol(Matrix *mit)
{
	Matrix *hova = Matrix_inic(mit->sor, mit->oszlop);
	for (int i = 0; i < mit->sor; ++i)
	{
		for (int j = 0; j < mit->oszlop; ++j)
		{
			hova->tomb[i][j] = mit->tomb[i][j];	
		}
	}
	return hova;
}
