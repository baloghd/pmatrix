#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "Matrix.h"
#include "Matrix_IO.h"
/** a kiírja a mátrixot **/
void Matrix_kiir(Matrix m)
{
    for (int i = 0; i < m.sor; ++i)
    {
        for (int j = 0; j < m.oszlop; ++j)
        {
             printf("%5.2f ", m.tomb[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/** a kiírja a mátrixot Octave-nak is jó formátumban **/
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
/** placeholder segédfüggvény (stackoverflow.com-ról)**/
int match(const char *s, const char *p, int overlap)
{
        int c = 0, l = strlen(p);

        while (*s != '\0') {
                if (strncmp(s++, p, l)) continue;
                if (!overlap) s += l - 1;
                c++;
        }
        return c;
}
/** sztringből beolvasott mátrix **/
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
/** a Matrix_sztringből megvalósítása lesz sztringkezelő függvények
 * okosabb használatával **/
Matrix Matrix_sztringbol_strtok(char *sz)
{
    char elval[2] = ",";
    char sorelval[2] = ";";
    char m[500] = "1,1,2,2,1,-1;4,4,8,9,1,-7;2,5,13,1,26,10;1,3,8,2,11,1;2,1,1,2,3,3;";
    char mcopy[500];
    strcpy(mcopy, m);
    char *sor, *oszlop, *sor_reent_ptr, *oszlop_reent_ptr;
    int n_sor = 0, n_oszlop = 0;
    
    //először megnézzük hány sora és oszlopa van a mátrixnak
    sor = strtok(m, sorelval);
    while (sor != NULL)
    {
		 //printf("%s\n", sor);
		 sor = strtok(NULL, sorelval);
		 n_sor++;
	}
	
    printf("%d sor \n", n_sor);
   
    oszlop = strtok(m, elval);
    
    while (oszlop != NULL)
    {
		 //printf("%s ", oszlop);
		 oszlop = strtok(NULL, elval);
		 n_oszlop++;
	}
	printf("%d oszlop\n", n_oszlop);
	Matrix vissza = Matrix_inic(n_sor, n_oszlop);
	
    int iter_sor = 0, iter_oszlop = 0;
    sor = strtok_r(mcopy, sorelval, &sor_reent_ptr);
	while (sor != NULL)
    {
		 oszlop = strtok_r(sor, elval, &oszlop_reent_ptr);
		 while (oszlop != NULL)
		 {
			printf("%s ", oszlop);
			char *e;
			//vissza.tomb[iter_sor][iter_oszlop] = strtod(oszlop, &e);
			oszlop = strtok_r(NULL, elval, &oszlop_reent_ptr);
			iter_oszlop++;
		 }
		 printf("\n");
		 sor = strtok_r(NULL, sorelval, &sor_reent_ptr);
		 iter_sor++;
	}

    return vissza;
}


Matrix Matrix_fajlbol(FILE *fp)
{
	int meret = 0;
	char buffer[512];
	while (fscanf(fp, "%s", buffer) != EOF)
        meret++;
    fseek(fp, 0, SEEK_SET);
    Matrix vissza = Matrix_inic(5 ,5);

    return vissza;
}

