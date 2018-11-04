#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Matrix.h"
#include "Matrix_IO.h"
#include "Matrix_muvelet.h"

double *sorszoroz(double *sor, int meret, double mivel)
{
    double *vissza = (double *) malloc(meret * sizeof(double));
    for (int i = 0; i < meret; ++i)
    {
        vissza[i] = sor[i] * mivel;
    }
    return vissza;
}

void sorszoroz_helyben(double *sor, int meret, double mivel)
{
    for (int i = 0; i < meret; ++i)
    {
        sor[i] *= mivel;
    }
}

double *sorosszead(double *sor1, double *sor2, int meret)
{
    double *vissza = (double *) malloc(meret * sizeof(double));
    for (int i = 0; i < meret; ++i)
    {
        vissza[i] = sor1[i] + sor2[i];
    }
    return vissza;
}

void sorosszead_helyben(double *sor1, double *sor2, int meret)
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
    assert(((m1.sor == m2.sor) && (m2.oszlop == m2.oszlop)) && "HIBA: csak azonos meretu Matrixok adhatoak ossze.");
    
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

int _van_meg_nemnulla_sor(Matrix m, int kezdosor)
{
    for (int i = kezdosor + 1; i < m.sor; ++i)
    {
        if (m.tomb[i][kezdosor] != 0)
            return i;
    }
    return -1;
}

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
        
        printf("sorszoroz:\n");
        
            
        Matrix_kiir(*m);
        for (int t = i + 1; t < k; ++t)
        {
            if (t == a)
                continue;
            double *bontosor = sorszoroz(m->tomb[i], n, -1*m->tomb[t][i]);
            printf("   %lf    ->", -1*m->tomb[t][i]);
            for (int z = 0; z < n; ++z)
                printf("%lf ", bontosor[z]);
            printf("\n");
            sorosszead_helyben(m->tomb[t], bontosor, n);
            free(bontosor);
            Matrix_kiir(*m);
        }
        
    }

}

void rref(Matrix *m)
{
    int k = m->sor;
    int n = m->oszlop;
    
    int l = 0;
    while (l < k)
    {
        double d, mult;
        
        for (int r = 0; r < k; ++r)
        {
            d = m->tomb[l][l];
            mult = m->tomb[r][l] / d;
            
            for (int c = 0; c < n; ++c)
            {
                if (r == l)
                    m->tomb[r][c] /= d;
                else
                    m->tomb[r][c] -= m->tomb[l][c] * mult;
            }
            
        }
        l++;
        Matrix_kiir(*m);
    }
    
    
}


/*
for (int i = 0; i < m->sor; ++i)
    {
        double generalo = m->tomb[i][i];
        int legnagyobb = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (m->tomb[j][i] > generalo)
            {
                generalo = m->tomb[j][i];
                legnagyobb = i;
            }
        }
        
        Matrix_sorcsere_helyben(m, i, legnagyobb);
        
        for (int k = i + 1; k < n; ++k)
        {
            double c = -m->tomb[k][i]/m->tomb[i][i];
            for (int l = i; l < n + 1; l++)
            {
                if (i == l)
                {
                    m->tomb[k][l] = 0;
                }
                else 
                {
                    m->tomb[k][l] += c * m->tomb[i][l];
                }
            }
        }
    }*/