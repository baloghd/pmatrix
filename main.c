#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "Matrix.h"
#include "Matrix_IO.h"
#include "Matrix_muvelet.h"

int main()
{
    //Matrix m = Matrix_identitas(3);
    //Matrix k = Matrix_sztringbol("12, 3, 4, 5;1, 8.5, 3, 2;");
    //Matrix a = Matrix_sztringbol("5, 6;4,4;7,-1;8,3;");
    //Matrix gg = Matrix_sztringbol("4,0,3,3;1,5,2,-1;5,4,8,4;");
    //Matrix gg = Matrix_sztringbol("1,1,2,2,1,-1;4,4,8,9,1,-7;2,5,13,1,26,10;1,3,8,2,11,1;2,1,1,2,3,3;");
    Matrix gg = Matrix_sztringbol("2,-1,6,12;2,2,3,24;6,-1,17,46;4,-1,13,32;");
    Matrix_kiir(gg);
    Matrix_Gauss(&gg);
    
    //rref(&gg);
    Matrix_kiir(gg);
 
    Matrix_memfelszab(&gg);
    return 0;
}
