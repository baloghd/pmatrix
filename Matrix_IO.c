#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "config.h"
#include "Matrix.h"
#include "Matrix_IO.h"
#include "debugmalloc.h"

/*! \file */ 

/*!
 *  \brief a kiírja a mátrixot
 *  \param m a mátrix
 */
void Matrix_kiir(Matrix *m)
{
	char *formatum = (char *) malloc(sizeof(char)*10);
	sprintf(formatum, "%%.%dlf ", PMATRIX_TIZEDES_PRECIZIO_KIIRAS);
    for (int i = 0; i < m->sor; ++i)
    {
        for (int j = 0; j < m->oszlop; ++j)
        {
			
			printf(formatum, m->tomb[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    free(formatum);
}
/*!
 *  \brief a kiírja a mátrixot Octave-kombatibilis formátumban
 *  \param m a mátrix
 */
void Matrix_kiir_Octave(Matrix *m)
{
    printf("[");
    for (int i = 0; i < m->sor; ++i)
    {
        for (int j = 0; j < m->oszlop; ++j)
        {
            if (j < m->oszlop - 1)
                printf("%f,", m->tomb[i][j]);
            else
                printf("%f", m->tomb[i][j]);
        }
        printf(";");
    }
    printf("]\n");
}
/*!
 *  \brief sztringből olvas be mátrixot
 *  \param Matrix_sztring a mátrixot tartalmazó sztring
 *  \param arg_n_sor ha tudjuk a mátrix sorainak számát \n ha nem, -1
 *  \param arg_n_oszlop ha tudjuk a mátrix oszlopainak számát \n ha nem, -1
 * 	\return a beolvasott mátrix struktúra
 */
Matrix *Matrix_sztringbol_strtok(const char *Matrix_sztring, int arg_n_sor, int arg_n_oszlop)
{
    char elval[2] = PMATRIX_OSZLOP_ELVALASZTO;
    char sorelval[2] = PMATRIX_SOR_ELVALASZTO;
    char *m = (char *) malloc(sizeof(char) * (strlen(Matrix_sztring) + 1));
    char *mcopy = (char *) malloc(sizeof(char) * (strlen(Matrix_sztring) + 1));
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
	
	Matrix *vissza = Matrix_inic(n_sor, n_oszlop);
    int iter_sor = 0, iter_oszlop = 0;
    sor = strtok_r(mcopy, sorelval, &sor_reent_ptr);
	while (sor != NULL)
    {
		 oszlop = strtok_r(sor, elval, &oszlop_reent_ptr);
		 while (oszlop != NULL)
		 {
			char *e;
			vissza->tomb[iter_sor][iter_oszlop++] = strtod(oszlop, &e);
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

void replace(char * o_string, char * s_string, char * r_string) {
      //a buffer variable to do all replace things
      char buffer[PMATRIX_BUFFER_MERET];
      //to store the pointer returned from strstr
      char *ch;
 
      //first exit condition
      if(!(ch = strstr(o_string, s_string)))
              return;
 
      //copy all the content to buffer before the first occurrence of the search string
      strncpy(buffer, o_string, ch-o_string);
 
      //prepare the buffer for appending by adding a null to the end of it
      buffer[ch-o_string] = 0;
 
      //append using sprintf function
      sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));
 
      //empty o_string for copying
      o_string[0] = 0;
      strcpy(o_string, buffer);
      //pass recursively to replace other occurrences
      return replace(o_string, s_string, r_string);
 }

/** 
 * \brief fájlból olvas be mátrixot \n
 * 
 * a fájl fejlécének figyelembe vételével 
 *  ami az alábbi formátumban van: \n
 * 		pmatrix_\<verzió\>_\<formátumkód\>_\<sorok száma\>_(opcionális sorelválasztó definíció)_\<oszlopok száma\>_(opcionális oszlopelválasztó definíció)
 * 			
 * 	valid formátumkódok: \n
 * 		**e**:\t egy sorban az egész mátrix definíció \n
 * 		**s**:\t a mátrix sorai a fájlban is soronként vannak \n
 *  \param fajlnev a mátrixot tartalmazó fájl neve
 *  \return a beolvasott mátrix struktúra
 * **/
Matrix *Matrix_fajlbol_olvas(char *fajlnev)
{
	/* a .mtrx kiterjesztésű fájloknak van fejléce */ 
	FILE *fp = fopen(fajlnev, "r");
    char buffer[PMATRIX_BUFFER_MERET];
    
    int sor = 0, oszlop = 0;
    Matrix_FAJLFORMATUM formatum;
    while (fgets(buffer, PMATRIX_BUFFER_MERET, fp))
    {
		if(strstr(buffer, "pmatrix"))
		{
			char *header = (char *) malloc(sizeof(char)*(strlen(buffer) + 1));
			strcpy(header, buffer);
			_fejlec_feldolgoz(header, &sor, &oszlop, &formatum);
			free(header);
			break;
		}
    }
    Matrix *vissza;
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
		fread(buffer, sizeof(char), PMATRIX_BUFFER_MERET, fp);
		replace(buffer, " ", PMATRIX_OSZLOP_ELVALASZTO);
		replace(buffer, "\n", PMATRIX_SOR_ELVALASZTO);
		vissza = Matrix_sztringbol_strtok(buffer, sor, oszlop);
	}
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
#define FORMATUMKOD "s"
void Matrix_fajlba_ir(Matrix *m, FILE *fp)
{
	/* fejléc, formátuma:
	 pmatrix_<v>_<ff>_<sor>_(<OPCIONÁLIS: egy_sor>)_<oszlop>_(<OPCIONÁLIS: egy_oszl>)
				v: pmatrix verzió
			   ff: fájlformátum kód
			  sor: sorok száma
	      egy_sor: egyedi sorelválasztó karakter
	       oszlop: oszlopok száma
	     egy_oszl: egyedi oszlopelválasztó karakter
	 * 
	 */
	char tizedes_prec[9];
	char *tizedes_prec_ws = (char *) malloc(sizeof(char)*10);
	sprintf(tizedes_prec, "%%.%dlf", PMATRIX_TIZEDES_PRECIZIO_FAJLBAIRAS);
	strcpy(tizedes_prec_ws, tizedes_prec);
	strcat(tizedes_prec_ws, " ");
	
	//a fájl fejléce
	fprintf(fp, "pmatrix_%s_%s_%d_%d_\n", PMATRIX_VERZIO,
										  FORMATUMKOD,
										  m->sor,
										  m->oszlop);
	for (int i = 0; i < m->sor; ++i)
    {
        for (int j = 0; j < m->oszlop; ++j)
        {
			//j < m->oszlop - 1: az adott elem az utolsó-e a sorban?
			//ha nem az, rakunk whitespace-t utána, ha az, akkor nem
			fprintf(fp, j < m->oszlop - 1 ? tizedes_prec_ws : tizedes_prec, m->tomb[i][j]);
        }
        if (i < m->sor - 1)
			fprintf(fp, "\n");
    }
    free(tizedes_prec_ws);
	fclose(fp);
}


