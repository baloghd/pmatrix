#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "config.h"
#include "Matrix.h"
#include "Matrix_IO.h"

/** a kiírja a mátrixot **/
void Matrix_kiir(Matrix m)
{
    for (int i = 0; i < m.sor; ++i)
    {
        for (int j = 0; j < m.oszlop; ++j)
        {
             printf("%.2f ", m.tomb[i][j]);
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

/** a Matrix_sztringből megvalósítása lesz sztringkezelő függvények
 * okosabb használatával **/
Matrix Matrix_sztringbol_strtok(const char *Matrix_sztring, int arg_n_sor, int arg_n_oszlop)
{
    char elval[2] = PMATRIX_OSZLOP_ELVALASZTO;
    char sorelval[2] = PMATRIX_SOR_ELVALASZTO;
    char *m = (char *) malloc(sizeof(char) * strlen(Matrix_sztring));
    char *mcopy = (char *) malloc(sizeof(char) * strlen(Matrix_sztring));
    strcpy(m, Matrix_sztring);
    strcpy(mcopy, Matrix_sztring);
   
    char *sor, *oszlop, *sor_reent_ptr, *oszlop_reent_ptr;
    int n_sor = 0, n_oszlop = 0;
    if (arg_n_sor == -1 || arg_n_oszlop == -1)
    {
		//ha nincs info, először megnézzük hány sora és oszlopa van a mátrixnak
		sor = strtok(m, sorelval);
		while (sor != NULL)
		{
			
			 sor = strtok(NULL, sorelval);
			 n_sor++;
		}
		
		oszlop = strtok(m, elval);
		while (oszlop != NULL)
		{
			 oszlop = strtok(NULL, elval);
			 n_oszlop++;
		}
	}
	else 
	{
		n_sor = arg_n_sor;
		n_oszlop = arg_n_oszlop;
	}

	Matrix vissza = Matrix_inic(n_sor, n_oszlop);
    int iter_sor = 0, iter_oszlop = 0;
    sor = strtok_r(mcopy, sorelval, &sor_reent_ptr);
	while (sor != NULL)
    {
		 oszlop = strtok_r(sor, elval, &oszlop_reent_ptr);
		 while (oszlop != NULL)
		 {
			char *e;
			vissza.tomb[iter_sor][iter_oszlop++] = strtod(oszlop, &e);
			oszlop = strtok_r(NULL, elval, &oszlop_reent_ptr);
		 }
		 sor = strtok_r(NULL, sorelval, &sor_reent_ptr);
		 iter_sor++;
		 iter_oszlop = 0;
	}
	
	free(m);
	free(mcopy);
    return vissza;
}

/** Matrix_fajlbol_olvas
 * 
 * fájlból olvas be mátrixot, a fájl fejlécének figyelembe vételével
 *  ami az alábbi formátumban van:
 * 		pmatrix<verzió>_<formátumkód>_<sorok száma>_(opcionális sorelválasztó definíció)_<oszlopok száma>_(opcionális oszlopelválasztó definíció)
 * 			
 * 	a valid formátumkódok:
 * 		e			egy sorban az egész mátrix definíció
 * 		s			a mátrix sorai a fájlban is soronként vannak 
 * 
 * **/
Matrix Matrix_fajlbol_olvas(char *fajlnev)
{
	/** a .mtrx kiterjesztésű fájloknak van fejléce **/ 
	FILE *fp = fopen(fajlnev, "r");
    char buffer[PMATRIX_BUFFER_MERET];
    
    int sor, oszlop;
    Matrix_FAJLFORMATUM formatum;
    
    while (fgets(buffer, PMATRIX_BUFFER_MERET, fp))
    {
		if(strstr(buffer, "pmatrix"))
		{
			char *header = (char *) malloc(sizeof(char)*strlen(buffer));
			strcpy(header, buffer);
			_fejlec_feldolgoz(header, &sor, &oszlop, &formatum);
			free(header);
			break;
		}
    }
    Matrix vissza;
    if (formatum == MATRIX_FF_EGYSORBAN)
    {
		while (fgets(buffer, PMATRIX_BUFFER_MERET, fp) != NULL)
		{
			// az fgets nem szedi le a newline karaktert,
			// a Matrix_sztringbol_strtok-nak viszont anélkül kell
			char *iter;
			if ((iter = strchr(buffer, '\n')) != NULL)
				*iter = '\0';
				
			vissza = Matrix_sztringbol_strtok(buffer, sor, oszlop);
		}
	}
	else 
	{
		vissza = Matrix_inic(sor, oszlop);
	}
    
    /*int iter_sor = 0, iter_oszlop = 0;
	while (fgets(buffer, PMATRIX_BUFFER_MERET, fp))
    {
		printf("buf: %s", buffer);
		
		
	}
	*/
    return vissza;
}

void _fejlec_feldolgoz(char *fejlec,
					  int *sor,
					  int *oszlop,
					  Matrix_FAJLFORMATUM *formatum)
{
	const char header_elvalaszto[2] = "_";
	char *token, *strtok_r_reentr;
	
	//a 'pmatrix' jelzőt átugorjuk
	token = strtok_r(fejlec, header_elvalaszto, &strtok_r_reentr);
	
	//a verziószámot is
	token = strtok_r(NULL, header_elvalaszto, &strtok_r_reentr);
	
	//formátumkód
	token = strtok_r(NULL, header_elvalaszto, &strtok_r_reentr);
	//alapértelmezetetten soronként ('s' formátumkód);
	//'e' formátumkódnál egy sorban az egész
	*formatum = MATRIX_FF_SORONKENT;
	if (strcmp(token, "e") == 0)
		*formatum = MATRIX_FF_EGYSORBAN;

	//sorok száma
	token = strtok_r(NULL, header_elvalaszto, &strtok_r_reentr);
	*sor = atoi(token);
	
	//sorelvalaszto, ha van
	if (*formatum == MATRIX_FF_EGYSORBAN)
	{
		token = strtok_r(NULL, header_elvalaszto, &strtok_r_reentr);
	}

	//oszlopok száma
	token = strtok_r(NULL, header_elvalaszto, &strtok_r_reentr);
	*oszlop = atoi(token);
	
	//oszlopelvalaszto, ha van
	if (*formatum == MATRIX_FF_EGYSORBAN)
	{
		token = strtok_r(NULL, header_elvalaszto, &strtok_r_reentr);
	}

}

void Matrix_fajlba_ir(FILE *fp)
{
	
}

