#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Matrix.h"
#include "Matrix_muvelet.h"

void sorszoroz(double *sor, int meret, double mivel)
{
    for (int i = 0; i < meret; ++i)
    {
        sor[i] *= mivel;
    }
}

void sorosszead(double *sor1, double *sor2, int meret)
{
    for (int i = 0; i < meret; ++i)
    {
        sor1[i] += sor2[i];
    }
}

void Matrix_sorcsere_helyben(Matrix *m, int egyiksor, int masiksor)
{
    double *tarolo = m->tomb[egyiksor];
    m->tomb[egyiksor] = m->tomb[masiksor];
    m->tomb[masiksor] = tarolo;
}

void Matrix_oszlopcsere_helyben(Matrix *m, int egyikoszlop, int masikoszlop)
{
    for (int i = 0; i < m->sor; ++i)
    {
        double tarolo = m->tomb[i][egyikoszlop];
        m->tomb[i][egyikoszlop] = m->tomb[i][masikoszlop];
        m->tomb[i][masikoszlop] = tarolo;
    }
}

Matrix Matrix_osszead(Matrix m1, Matrix m2)
{
    assert(((m1.sor == m2.sor) && (m2.oszlop == m2.oszlop)) &&
                "HIBA: csak azonos meretu Matrixok adhatoak ossze.");
    Matrix t = Matrix_inic(m1.sor, m1.oszlop);

    for (int i = 0; i < m1.sor; ++i)
    {
        for (int j = 0; j < m1.oszlop; ++j)
        {
            t.tomb[i][j] = m1.tomb[i][j] + m2.tomb[i][j];
        }
    }

    return t;
}

Matrix Matrix_szorzas(Matrix jobb, Matrix bal)
{
    assert(((jobb.sor == bal.oszlop) && (jobb.oszlop == bal.sor)) && "HIBA: szorzando Matrixok dimenzioira igaznak kell lennie, hogy [i x j] * [j x i]");
    Matrix szorzat = Matrix_inic(jobb.sor, bal.oszlop);
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
            szorzat.tomb[i][j] = sum;
        }
    }
    return szorzat;
}



void Matrix_Gauss(Matrix m)
{
    for (int i = 0; i < m.sor; ++i)
    {
        double generalo = m.tomb[i][i];
        if (generalo == 0)
        {
            int nullassorindex = 0;
            for (int j = 0; j < m.sor; ++j)
            {
                if (m.tomb[j][i] == 0)
                {
                    nullassorindex = j;
                    break;
                }
            }
            printf("csereljuk a %d. sort %d.-re\n", m.sor-1, nullassorindex);
            Matrix_sorcsere_helyben(&m, m.sor-1, nullassorindex);
            generalo = m.tomb[i][i];
        }
        Matrix_kiir(m);
        printf("vezeregyes az %d. sorban, generalo = %d!\n", i + 1, generalo);
        sorszoroz(m.tomb[i], m.oszlop, -1/generalo);
        
        
        double nullazando;
        for (int j = i + 1; j < m.sor; ++j)
        {
            nullazando = m.tomb[j][i];
            printf("a nullazando: %lf \n", nullazando);
            if (nullazando > 1)
            {
                sorszoroz(m.tomb[i], m.oszlop, nullazando);
            }
            sorosszead(m.tomb[j], m.tomb[i], m.oszlop);
            sorszoroz(m.tomb[i], m.oszlop, 1/nullazando);
            
            Matrix_kiir(m);
        }
        sorszoroz(m.tomb[i], m.oszlop, -1);
    }
}