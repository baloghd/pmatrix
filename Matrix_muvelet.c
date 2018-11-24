#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "Matrix.h"
#include "Matrix_IO.h"
#include "Matrix_muvelet.h"
#include "debugmalloc.h"

/** megszorozza egy sor összes elemét egy számmal, új sort visszaadva **/
double *sorszoroz(double *sor, int meret, double mivel)
{
    double *vissza = (double *) malloc(meret * sizeof(double));
    for (int i = 0; i < meret; ++i)
    {
        vissza[i] = sor[i] * mivel;
    }
    return vissza;
}
/** megszorozza egy paraméterként kapott sor összes elemét egy számmal**/
void sorszoroz_helyben(double *sor, int meret, double mivel)
{
    for (int i = 0; i < meret; ++i)
    {
        sor[i] *= mivel;
    }
}
/** összeadja egy paraméterként kapott sor összes elemét egy számmal**/
double *sorosszead(double *sor1, double *sor2, int meret)
{
    double *vissza = (double *) malloc(meret * sizeof(double));
    for (int i = 0; i < meret; ++i)
    {
        vissza[i] = sor1[i] + sor2[i];
    }
    return vissza;
}
/** összeadja egy paraméterként kapott sor összes elemét egy számmal**/
void sorosszead_helyben(double *sor1, double *sor2, int meret)
{
    for (int i = 0; i < meret; ++i)
    {
        sor1[i] += sor2[i];
    }
}
/*** http://mathworld.wolfram.com/MatrixTrace.html ***/
double Matrix_nyom(Matrix *m)
{
    assert(m->sor == m->oszlop);
    double nyom = 0;
    for (int i = 0; i < m->sor; ++i)
    {
        nyom += m->tomb[i][i];
    }
    return nyom;
}
/** megcseréli egy paraméterként kapott mátrix megadott sorait (0-tól indexelve) **/
void Matrix_sorcsere_helyben(Matrix *m, int egyiksor, int masiksor)
{
    double *tarolo = m->tomb[egyiksor];
    m->tomb[egyiksor] = m->tomb[masiksor];
    m->tomb[masiksor] = tarolo;
}
/** megcseréli egy paraméterként kapott mátrix megadott oszlopait (0-tól indexelve) **/
void Matrix_oszlopcsere_helyben(Matrix *m, int egyikoszlop, int masikoszlop)
{
    for (int i = 0; i < m->sor; ++i)
    {
        double tarolo = m->tomb[i][egyikoszlop];
        m->tomb[i][egyikoszlop] = m->tomb[i][masikoszlop];
        m->tomb[i][masikoszlop] = tarolo;
    }
}
/** összead két mátrixot **/
Matrix *Matrix_osszead(Matrix m1, Matrix m2)
{
    assert(((m1.sor == m2.sor) && (m2.oszlop == m2.oszlop)) && "HIBA: csak azonos meretu Matrixok adhatoak ossze.");
    
    Matrix *t = Matrix_inic(m1.sor, m1.oszlop);

    for (int i = 0; i < m1.sor; ++i)
    {
        for (int j = 0; j < m1.oszlop; ++j)
        {
            t->tomb[i][j] = m1.tomb[i][j] + m2.tomb[i][j];
        }
    }

    return t;
}
/** megszoroz két mátrixot **/
Matrix *Matrix_szorzas(Matrix jobb, Matrix bal)
{
    assert(((jobb.sor == bal.oszlop) && (jobb.oszlop == bal.sor)) && "HIBA: szorzando Matrixok dimenzioira igaznak kell lennie, hogy [i x j] * [j x i]");
    
    Matrix *szorzat = Matrix_inic(jobb.sor, bal.oszlop);
    for (int i = 0; i < jobb.sor; ++i)
    {
        int j, k;
        for (j = 0; j < bal.oszlop; ++j)
        {
            double sum = 0;
            for (k = 0; k < jobb.oszlop; ++k)
            {
                sum += jobb.tomb[i][k] * bal.tomb[k][j];
            }
            szorzat->tomb[i][j] = sum;
        }
    }
    return szorzat;
}
/** segédfüggvény a Gauss-eliminációhoz **/
int _van_meg_nemnulla_sor(Matrix m, int kezdosor)
{
    for (int i = kezdosor + 1; i < m.sor; ++i)
    {
        if (m.tomb[i][kezdosor] != 0)
            return i;
    }
    return -1;
}
/*** a Gauss elimináció még nem 100%-osan működő ***/
Matrix* Matrix_Gauss(Matrix *m)
{
	Matrix *masol = Matrix_masol(m);
    int a;
    for (int i = 0; i < masol->sor; ++i)
    {
        if (masol->tomb[i][i] != 0)
        {
            sorszoroz_helyben(masol->tomb[i], masol->oszlop, 1/masol->tomb[i][i]);
        }
        else
        {
            a = _van_meg_nemnulla_sor(*m, i);
            if (a > 0)
            {
                Matrix_sorcsere_helyben(m, i, a);
                sorszoroz_helyben(masol->tomb[i], masol->oszlop, 1/masol->tomb[i][i]);
            }
            else 
            {
                continue;
            }
        }
        for (int t = i + 1; t < masol->sor; ++t)
        {
            if (t == a)
                continue;
            double *bontosor = sorszoroz(masol->tomb[i], masol->oszlop, -1*masol->tomb[t][i]);
            sorosszead_helyben(masol->tomb[t], bontosor, masol->oszlop);
            free(bontosor);
        }
    }
    //redukált lépcsős alak
    double nullazando;
    for (int i = (masol->sor)-1; i >= 0; --i)
    {
		for (int j = (masol->oszlop)-1; j >= 0; --j)
		{
			if (i == j)
			{
				//double pivot = masol->tomb[i][j];
				for (int k = i - 1; k >= 0; k--)
				{
					double *bontosor = masol->tomb[i];
					nullazando = masol->tomb[k][j];
					bontosor = sorszoroz(bontosor, masol->oszlop, -nullazando);
					sorosszead_helyben(masol->tomb[k], bontosor, masol->oszlop);
					free(bontosor);
				}
			}
		}
	}
    return masol;
}
/** segédfüggvény a Gauss-eliminációhoz és a rang kiszámításához **/
bool _nullasor(double *sor, int meret)
{
	for (int i = 0; i < meret; ++i)
	{
		if (sor[i] != 0)
			return false;
	}
	return true;
}

int Matrix_rang(Matrix *m)
{
	Matrix *masol_m = Matrix_masol(m);
	Matrix *redukalt_m = Matrix_Gauss(masol_m);
	int rang = 0;
	//a nulla elemű mátrix rangja 0 
	if (redukalt_m->sor == 0 || redukalt_m->oszlop == 0)
		return rang;
	for (int i = 0; i < redukalt_m->sor; ++i)
	{
		//ha a sor nem nullás sor, a rang eggyel növekszik
		if (!_nullasor(redukalt_m->tomb[i], redukalt_m->oszlop))
			rang++;
	}
	Matrix_memfelszab(redukalt_m);
	Matrix_memfelszab(masol_m);
	return rang;
}

Matrix *Matrix_inverz(Matrix *m)
{
	assert((m->sor == m->oszlop) && "HIBA: csak négyzetes mátrixnak van inverze.");
	Matrix *osszerak = Matrix_jobbra_hozzaad(m);
	Matrix *eliminal = Matrix_Gauss(osszerak);
	Matrix *inverz = Matrix_balrol_elvesz(eliminal);
	
	Matrix_memfelszab(osszerak);
	Matrix_memfelszab(eliminal);
	return inverz;
}

Matrix *Matrix_jobbra_hozzaad(Matrix *m)
{
	assert((m->sor == m->oszlop) && "HIBA: csak négyzetes mátrixokra működik.");
	Matrix *egyseg = Matrix_egyseg(m->sor);
	Matrix *osszerakott = Matrix_inic(m->sor, 2 * m->oszlop);
	for (int i = 0; i < osszerakott->sor; ++i)
	{
		for (int j = 0; j < osszerakott->oszlop; ++j)
		{
			if (j >= m->oszlop)
				osszerakott->tomb[i][j] = egyseg->tomb[i][j - m->oszlop];
			else
				osszerakott->tomb[i][j] = m->tomb[i][j];
		}
	}
	Matrix_memfelszab(egyseg);
	return osszerakott;
}

Matrix *Matrix_balrol_elvesz(Matrix *m)
{
	int vissza_oszlopok_szama = m->oszlop / 2;
	Matrix *vissza = Matrix_inic(m->sor, vissza_oszlopok_szama);
	for (int i = 0; i < m->sor; ++i)
	{
		for (int j = vissza_oszlopok_szama; j < m->oszlop; ++j)
		{
			vissza->tomb[i][j - vissza_oszlopok_szama] = m->tomb[i][j];	
		}
	}
	return vissza;
}


