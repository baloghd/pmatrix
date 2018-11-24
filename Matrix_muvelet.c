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
void Matrix_Gauss(Matrix *m)
{
    int k = m->sor;
    int n = m->oszlop;
    int a;
    for (int i = 0; i < k; ++i)
    {
        if (m->tomb[i][i] != 0)
        {
            sorszoroz_helyben(m->tomb[i], n, 1/m->tomb[i][i]);
        }
        else
        {
            a = _van_meg_nemnulla_sor(*m, i);
            a > 0 ? printf("%d van, %d\n", i, a) : printf("%d nincs, %d\n", i, a);
            if (a > 0)
            {
                Matrix_sorcsere_helyben(m, i, a);
                sorszoroz_helyben(m->tomb[i], n, 1/m->tomb[i][i]);
            }
            else 
            {
                continue;
            }
        }
        
        Matrix_kiir(*m);
        for (int t = i + 1; t < k; ++t)
        {
            if (t == a)
                continue;
            double *bontosor = sorszoroz(m->tomb[i], n, -1*m->tomb[t][i]);
            printf("   %lf    ->", -1*m->tomb[t][i]);
			printf("\n");
            for (int z = 0; z < n; ++z)
                printf("%lf ", bontosor[z]);
            sorosszead_helyben(m->tomb[t], bontosor, n);
            free(bontosor);
            Matrix_kiir(*m);
        }
        
    }

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

/**egyelőre redukált alakú mátrixot kapva adja vissza a rangját **/
/** TODO: beépíteni az eliminációt **/
int Matrix_rang(const Matrix m)
{
	int rang = 0;
	
	//a nulla elemű mátrix rangja 0 
	if (m.sor == 0 || m.oszlop == 0)
		return rang;

	for (int i = 0; i < m.sor; ++i)
	{
		//ha a sor nem nullás sor, a rang eggyel növekszik
		if (!_nullasor(m.tomb[i], m.oszlop))
			rang++;
	}
	return rang;
} 
