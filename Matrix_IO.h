#ifndef MATRIX_IO
#define MATRIX_IO

#include <string.h>

#include "Matrix.h"

/*! \file */ 

/*!
 * \brief a fájlba írt mátrix lehetséges formátumai
 */
typedef enum Matrix_FAJLFORMATUM {
	/*! a kiírandó fájl első sora a fejléc, a második sora a mátrix*/
	MATRIX_FF_EGYSORBAN,
	/*! a kiírandó fájl első sora a fejléc, a mátrix ezután soronként íródik bele*/
	MATRIX_FF_SORONKENT
} Matrix_FAJLFORMATUM;


void Matrix_kiir(Matrix *m);

void Matrix_kiir_Octave(Matrix *m);

Matrix *Matrix_sztringbol_strtok(const char *sz, int n_sor, int n_oszlop);

Matrix *Matrix_fajlbol_olvas(char *fajlnev);

void _fejlec_feldolgoz(char *fejlec,
					  int *sor,
					  int *oszlop,
					  Matrix_FAJLFORMATUM *formatum);  
					  
void Matrix_fajlba_ir(Matrix *m, FILE *fp);
#endif

