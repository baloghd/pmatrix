#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "config.h"
#include "Matrix.h"
#include "Matrix_IO.h"
#include "Matrix_muvelet.h"

int main()
{
    //Matrix k = Matrix_sztringbol("12, 3, 4, 5;1, 8.5, 3, 2;");
    //Matrix a = Matrix_sztringbol("5, 6;4,4;7,-1;8,3;");
    //Matrix gg = Matrix_sztringbol("0,1,2;1,2,1;2,7,8;");
    //Matrix gg = Matrix_sztringbol_strtok("1,1,2,2,1,-1;4,4,8,9,1,-7;2,5,13,1,26,10;1,3,8,2,11,1;2,1,1,2,3,3;");
    //Matrix gg = Matrix_sztringbol_strtok("2,-1,6,12;2,2,3,24;6,-1,17,46;4,-1,13,32;");
    //Matrix_Gauss(&gg);
    //Matrix_kiir(gg);
    //Matrix_Gauss(&gg);
    //Matrix_kiir(gg);
    
    //Matrix rref_gg = Matrix_sztringbol("1,2,1;0,1,2;0,0,0;");
    //printf("a rref_gg rangja: %d\n", Matrix_rang(rref_gg));
    
 
    
    /* printf("pmatrix_%d.%d_%s_%s_§", PMATRIX_VERZIO,
									PMATRIX_ALVERZIO,
									PMATRIX_SOR_ELVALASZTO,
									PMATRIX_OSZLOP_ELVALASZTO);
	*/
	
    
    Matrix gg = Matrix_fajlbol_olvas("TESZTMATRIX.mtrx");
    Matrix_kiir(gg);
    printf("beolvasas 1. sikerult\n");
    
    FILE *output = fopen("TESZT_KI.mtrx", "w");
    Matrix_fajlba_ir(gg, output);
    printf("kiiras sikerult\n");
    
    Matrix_memfelszab(&gg);
    Matrix ff = Matrix_fajlbol_olvas("TESZT_KI.mtrx");
    Matrix_kiir(ff);
    printf("beolvasas 2. sikerult\n");
    
    return 0;
}
