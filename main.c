#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "Matrix.h"
#include "Matrix_IO.h"
#include "Matrix_muvelet.h"

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

int main()
{
    //Matrix m = Matrix_identitas(3);
    //Matrix k = Matrix_sztringbol("12, 3, 4, 5;1, 8.5, 3, 2;");
    //Matrix a = Matrix_sztringbol("5, 6;4,4;7,-1;8,3;");
    //Matrix gg = Matrix_sztringbol("4,0,3,3;1,5,2,-1;5,4,8,4;");
    Matrix gg = Matrix_sztringbol("1,1,2,2,1,-1;4,4,8,9,1,-7;2,5,13,1,26,10;1,3,8,2,11,1;2,1,1,2,3,3;");
    //Matrix_sorcsere_helyben(&a, 0, 1);
    //Matrix_oszlopcsere_helyben(&a, 0, 1);

    //Matrix_kiir(Matrix_szorzas(k, a));
    Matrix_kiir(gg);
    Matrix_kiir_Octave(gg);
    //Matrix_Gauss(gg);
    //Matrix_kiir(gg);
    Matrix_memfelszab(&gg);

    return 0;
}