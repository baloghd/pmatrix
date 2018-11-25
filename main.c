#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "config.h"
#include "Matrix.h"
#include "Matrix_IO.h"
#include "Matrix_muvelet.h"
//#include "debugmalloc.h"

void demo_sokcsillag()
{
	for (int i = 0; i < 50; ++i)
		printf("*");
	printf("\n");
}

int main()
{
	demo_sokcsillag();
	printf("		pmatrix %s DEMÓ\n", PMATRIX_VERZIO);
	demo_sokcsillag();
	
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
	
	Matrix *also = Matrix_egyseg(transzf_A->sor);
	Matrix *felso = Matrix_masol(transzf_A);
	LU_dekomp(*transzf_A, also, felso);
	
	printf("a mátrixnak az LU-dekompozíciója:\n");
	printf("alsóháromszög-mátrix:\n");
	Matrix_kiir(also);

	printf("felsőháromszög-mátrix:\n");
	Matrix_kiir(felso);
	
	printf("most kiírjuk a felsőháromszög-mátrixot egy fájlba, egysoros mtrx formátumban\n");
	Matrix_fajlba_ir(felso, "transzf_A_felso", "mtrx", "e");
	
	printf("most visszaolvassuk ugyanezt:\n");
	Matrix *egysor_beolvas = Matrix_fajlbol_olvas("transzf_A_felso.mtrx");
	Matrix_kiir(egysor_beolvas);
	
	printf("adjuk össze az alsó- és felsőháromszögmátrixokat: \n");
	Matrix *osszeg = Matrix_osszead(*also, *felso);
	Matrix_kiir(osszeg);
	
	Matrix_memfelszab(A);
	Matrix_memfelszab(A_inv);
	Matrix_memfelszab(szorzat);
	Matrix_memfelszab(transzf_A);
	Matrix_memfelszab(transzf_A_T);
	Matrix_memfelszab(also);
	Matrix_memfelszab(felso);
	Matrix_memfelszab(egysor_beolvas);
	Matrix_memfelszab(osszeg);
	
    return 0;
}
