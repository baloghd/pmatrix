#include <stdio.h>

#include "Matrix.h"
#include "Matrix_IO.h"

void Matrix_kiir(Matrix m)
{
    for (int i = 0; i < m.sor; ++i)
    {
        for (int j = 0; j < m.oszlop; ++j)
        {
             printf("%5.5f ", m.tomb[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Matrix_kiir_Octave(Matrix m)
{
    printf("[");
    for (int i = 0; i < m.sor; ++i)
    {
        for (int j = 0; j < m.oszlop; ++j)
        {
            if (j < m.oszlop - 1)
                printf("%f,", m.tomb[i][j]);
            else
                printf("%f", m.tomb[i][j]);
        }
        printf(";");
    }
    printf("]\n");
}

Matrix Matrix_sztringbol(char *sz)
{
    //standard elvalasztok:
    // ,    elemek
    // ;    sorok
    // tehat 1,2,3;4,5,6 =
    // [1 2 3
    //  4 5 6]
    char elval[] = ",";
    char sorelval[] = ";";
    int ssor = match(sz, sorelval, 0);
    int ooszlop = (match(sz, elval, 0) + ssor) / ssor;

    Matrix k = Matrix_inic(ssor, ooszlop);

    char *p = sz, *ujo = strstr(p, ";");
    double d;
    int oszlop = 0;
    int sor = 0;

    while (true)
    {
        sscanf(p, "%lf", &(k.tomb[sor][oszlop]));
        oszlop++;
        p = strstr(p, elval);

        if ((p - ujo) >= 0)
        {
            sor++;
            p = ujo;
            p++;
            ujo = strstr(p, sorelval);
            oszlop = 0;
        }
        else
        {
            if (p != NULL)
            {
                p++;
            }
            else
            {
                break;
            }
        }
    }
    return k;
}

Matrix Matrix_sztringbol_strtok(char *sz)
{
    char elval[2] = ",";
    char sorelval[2] = ";";
    char m[500] = "1,1,2,2,1,-1;4,4,8,9,1,-7;2,5,13,1,26,10;1,3,8,2,11,1;2,1,1,2,3,3;";
    char *sor, *oszlop;
    sor = strtok(m, sorelval);
    printf("%s", sor);
}

/* Matrix Matrix_fajlbol(FILE *fp)
{
    
}
*/