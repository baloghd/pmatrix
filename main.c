#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "config.h"
#include "Matrix.h"
#include "Matrix_IO.h"
#include "Matrix_muvelet.h"
#include "debugmalloc.h"

int main()
{
	printf("pmatrix %s DEMÓ\n", PMATRIX_VERZIO);

	//Matrix *A = Matrix_fajlbol_olvas("TESZT_KI.mtrx");
	Matrix *A = Matrix_sztringbol("4,5,10,12;6,7,8,-5;3,4,8,18;5,6,7,1;", -1, -1);	
	printf("mátrix A:\n");
	Matrix_kiir(A);
	
	printf("det(A): %.4lf\n", Matrix_determinans(A));
	printf("rang(A): %d\n", Matrix_rang(A));
	printf("nyom(A): %.4lf\n\n", Matrix_nyom(A));
	Matrix *A_inv = Matrix_inverz(A);
	printf("A_inverz: \n");
	Matrix_kiir(A_inv);
	
	printf("A * A_inverz = E:\n");
	Matrix *szorzat = Matrix_szorzas(*A, *A_inv);
	Matrix_kiir(szorzat);
	
	printf("A első és harmadik sora, majd második és negyedik oszlopa megcserélve:\n");
	Matrix_sorcsere_helyben(A, 0, 2);
	Matrix_oszlopcsere_helyben(A, 1, 3);
	Matrix_kiir(A);
	
	printf("ezt a transzformált mátrixot kíírjuk fájlba, transzf_A.mtrx néven\n");
	Matrix_fajlba_ir(A, "transzf_A", "mtrx", "s");
	
	printf("most beolvassuk, majd kiírjuk a transzponáltját:\n");
	Matrix *transzf_A = Matrix_fajlbol_olvas("transzf_A.mtrx");
	Matrix *transzf_A_T = Matrix_transzponal(transzf_A);
	Matrix_kiir(transzf_A_T);

	Matrix_memfelszab(A);
	Matrix_memfelszab(A_inv);
	Matrix_memfelszab(szorzat);
	Matrix_memfelszab(transzf_A);
	Matrix_memfelszab(transzf_A_T);
	
    return 0;
}
