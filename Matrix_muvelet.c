#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "config.h"
#include "Matrix.h"
#include "Matrix_IO.h"
#include "Matrix_muvelet.h"
#include "debugmalloc.h"

/*! \file */ 

/*!
 *  \brief megszorozza egy sor összes elemét egy számmal, új sort visszaadva
 *  \param sor a szorzandó double tömb
 * 	\param meret a tömb mérete
 *  \param mivel a szorzó
 * 	\return a megszorzott tömbre mutató, újonnan lefoglalt memóriaterületre
 * 	mutató pointer
 */
double *sorszoroz(double *sor, int meret, double mivel)
{
    double *vissza = (double *) malloc(meret * sizeof(double));
    for (int i = 0; i < meret; ++i)
    {
        vissza[i] = sor[i] * mivel;
    }
    return vissza;
}

/*!
 *  \brief megszorozza egy sor összes elemét egy számmal, helyben
 *  \param sor a szorzandó double tömb
 * 	\param meret a tömb mérete
 *  \param mivel a szorzó
 */
void sorszoroz_helyben(double *sor, int meret, double mivel)
{
    for (int i = 0; i < meret; ++i)
    {
        sor[i] *= mivel;
    }
}
/*!
 *  \brief hozzáad egy sort egy másik sorhoz, új sort visszaadva
 *  \param sor1 az összeadás egyik tagja
 * 	\param sor2 az összeadás másik tagja
 * 	\param meret a tömb mérete
 * 	\return az újonnan lefoglalt memóriaterületre mutató pointer
 */
double *sorosszead(double *sor1, double *sor2, int meret)
{
    double *vissza = (double *) malloc(meret * sizeof(double));
    for (int i = 0; i < meret; ++i)
    {
        vissza[i] = sor1[i] + sor2[i];
    }
    return vissza;
}
/*!
 *  \brief egy sorhoz ad egy másikat, helyben
 *  \param sor1 amihez adunk
 * 	\param sor2 amit 
 *  \param meret a sorok mérete
 */
void sorosszead_helyben(double *sor1, double *sor2, int meret)
{
    for (int i = 0; i < meret; ++i)
    {
        sor1[i] += sor2[i];
    }
}
/*!
 *  \brief egy mátrix főátlójának összege, _nyom_
 *  \param m a mátrix
 * 	\return a főátló összege
 */
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
/*!
 *  \brief megcseréli egy paraméterként kapott mátrix megadott sorait (0-tól indexelve)
 *  \param m a mátrix
 *  \param egyiksor az egyik megcserélendő sor
 * 	\param másiksor a másik megcserélendő sor
 */
void Matrix_sorcsere_helyben(Matrix *m, int egyiksor, int masiksor)
{
    double *tarolo = m->tomb[egyiksor];
    m->tomb[egyiksor] = m->tomb[masiksor];
    m->tomb[masiksor] = tarolo;
}
/*!
 *  \brief megcseréli egy paraméterként kapott mátrix megadott oszlopait (0-tól indexelve) 
 *  \param m a mátrix
 *  \param egyikoszlop az egyik megcserélendő oszlop
 * 	\param másikoszlop a másik megcserélendő oszlop
 */
void Matrix_oszlopcsere_helyben(Matrix *m, int egyikoszlop, int masikoszlop)
{
    for (int i = 0; i < m->sor; ++i)
    {
        double tarolo = m->tomb[i][egyikoszlop];
        m->tomb[i][egyikoszlop] = m->tomb[i][masikoszlop];
        m->tomb[i][masikoszlop] = tarolo;
    }
}
/*!
 *  \brief összead két mátrixot
 *  \param m1 az összeadás jobb oldala
 *  \param m2 az összeadás bal oldala
 *  \return az eredmény mátrixára mutató pointer (újonnan lefoglalt terület)
 */
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
/*!
 *  \brief megszoroz két mátrixot
 *  \param jobb az összeadás jobb oldala
 *  \param bal az összeadás bal oldala
 *  \return az eredmény mátrixára mutató pointer (újonnan lefoglalt terület)
 */
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

void Matrix_transzponal(Matrix *m)
{
	Matrix *m_T = Matrix_inic(m->sor, m->oszlop);
	for (int i = 0; i < m->sor; ++i)
    {
        for (int j = 0; j < m->oszlop; ++j)
        {
			m_T->tomb[j][i] = m->tomb[i][j];
		}
	}
	m = m_T;
	Matrix_memfelszab(m);
}



/*!
 *  \brief segédfüggvény a Gauss-eliminációhoz
 *  \param m a mátrix
 *  \param kezdosor az első sor, amitől lefelé vizsgálódunk (ahol a pivot elem van éppen)
 *  \return a megtalált, a pivot alatt nem 0 elemet tartalmazó sor indexe, ha van ilyen\n
 * 	különben a sikertelen keresést jelző -1
 */
int _van_meg_nemnulla_sor(Matrix m, int kezdosor)
{
    for (int i = kezdosor + 1; i < m.sor; ++i)
    {
        if (m.tomb[i][kezdosor] != 0)
            return i;
    }
    return -1;
}
/*!
 *  \brief Gauss-elimináció implementáció
 *  \param m a mátrix
 *  \return az eliminált mátrix
 * TODO: lépcsős / redukált lépcsős alak választás
 */
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
            a = _van_meg_nemnulla_sor(*masol, i);
            if (a > 0)
            {
                Matrix_sorcsere_helyben(masol, i, a);
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
/*!
 *  \brief segédfüggvény a Gauss-eliminációhoz és a rang kiszámításához
 *  \param sor a vizsgált tömb
 *  \param meret a sor (tömb) mérete
 *  \return _true_: ha a sor csak 0-t tartalmaz \n _false_: egyébként
 * 
 */
bool _nullasor(double *sor, int meret)
{
	for (int i = 0; i < meret; ++i)
	{
		if (sor[i] != 0)
			return false;
	}
	return true;
}
/*!
 *  \brief egy mátrix rangját számítja ki
 *  \param m a mátrix
 *  \return a mátrix sorrangja (= oszloprang = determinánsrang)
 */
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
/*!
 *  \brief segédfüggvény double-k összehasonlítására
 *  \param x egyik szám
 *  \param y másik szám
 *  \return _true_: a PMATRIX_EPSILON határon belül vannak, tehát ~egyenlőek \n
 * _false_: nem egyenlőek
 */
bool _double_egyenlo(double x, double y)
{
	return fabs(x - y) < PMATRIX_EPSILON;
}

/*!
 *  \brief egy mátrix inverzét adja vissza
 *  \param m a mátrix
 *  \return a mátrix inverzére mutató pointer
 */
Matrix *Matrix_inverz(Matrix *m)
{
	assert((m->sor == m->oszlop) && "HIBA: csak négyzetes mátrixnak van inverze.");
	assert(!_double_egyenlo(0.0, Matrix_determinans(m)) && "HIBA: a mátrix szinguláris (determinánsa 0), így nincs inverze");
	
	Matrix *osszerak = Matrix_jobbra_hozzaad(m);
	Matrix *eliminal = Matrix_Gauss(osszerak);
	Matrix *inverz = Matrix_balrol_elvesz(eliminal);
	
	Matrix_memfelszab(osszerak);
	Matrix_memfelszab(eliminal);
	return inverz;
}
/*!
 *  \brief segédfüggvény az inverz kiszámításához
 *  \param m a mátrix
 *  \return az eredeti mátrix és egy melléírt, azonos méretű egységmátrix
 */
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
/*!
 *  \brief segédfüggvény az inverz kiszámításához
 *  \param m egy, balról az egységmátrixot, jobbról
 *  az eliminációval megtalált inverzet tartalmazó mátrix
 *  \return a mátrix "jobb fele", azaz az eredeti mátrix inverze
 */
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
/*!
 *  \brief egy matrix determinansanak kiszamitasa
 *  \param m a vizsgalt matrix
 * 	\return a determinans
 */
double Matrix_determinans(Matrix *m)
{
	assert(m->sor == m->oszlop);
	Matrix *also = Matrix_egyseg(m->sor);
	Matrix *felso = Matrix_masol(m);
	LU_dekomp(*m, also, felso);
	Matrix_memfelszab(also);
	double vissza = _Matrix_det_foatlo_szorzas(felso);
	Matrix_memfelszab(felso);
	return vissza;
	}
/*!
 *  \brief segédfüggvény determináns-számításhoz, egy mátrix főátlójának szorzata
 *  \param m a mátrix
 * 	\return a főátló szorzata
 */
double _Matrix_det_foatlo_szorzas(Matrix *m)
{
    assert(m->sor == m->oszlop);
    double det = 1;
    for (int i = 0; i < m->sor; ++i)
    {
        det *= m->tomb[i][i];
    }
    return det;
}
/*!
 *  \brief LU-dekompozicio
 *  \param m a szetszedendo matrix
 * 	\param also egy egysegmatrixra mutato pointer, ami also
 *  haromszogmatrix lesz ha lefut a fuggveny
 *  \param masol egy inicializalt matrix
 */
void LU_dekomp(Matrix m, Matrix *also, Matrix *masol)
{
    for (int i = 0; i < masol->sor; ++i)
    {
        if (masol->tomb[i][i] != 0)
        {
            //sorszoroz_helyben(masol->tomb[i], masol->oszlop, 1/masol->tomb[i][i]);
        }
        else
        {
            /*a = _van_meg_nemnulla_sor(*m, i);
            if (a > 0)
            {
                Matrix_sorcsere_helyben(m, i, a);
                sorszoroz_helyben(masol->tomb[i], masol->oszlop, 1/masol->tomb[i][i]);
            }
            else 
            {
                continue;
            }*/
        }
        for (int t = i + 1; t < masol->sor; ++t)
        {
            double *bontosor = sorszoroz(masol->tomb[i], masol->oszlop, -(masol->tomb[t][i]/masol->tomb[i][i]));
            //printf("számok: %lf %lf együttható: %lf\n", masol->tomb[t][i], masol->tomb[i][i], masol->tomb[t][i]/masol->tomb[i][i]);
            also->tomb[t][i] = masol->tomb[t][i]/masol->tomb[i][i];
            sorosszead_helyben(masol->tomb[t], bontosor, masol->oszlop);
            free(bontosor);
        }
    }
}
