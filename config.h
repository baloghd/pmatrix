/*! \file */ 

//általános
/*! a pmatrix verziószám */
#define PMATRIX_VERZIO 1
/*! a pmatrix alverziószám */
#define PMATRIX_ALVERZIO 0
/*! tizedes precízió a standard kimenetre való írásnál */
#define PMATRIX_TIZEDES_PRECIZIO_KIIRAS 2
/*! tizedes precízió fájlba való írásnál */
#define PMATRIX_TIZEDES_PRECIZIO_FAJLBAIRAS 2

//IO
/*! sorelválasztó karakter, alapértelmezésben ";" */
#ifndef PMATRIX_SOR_ELVALASZTO
#define PMATRIX_SOR_ELVALASZTO ";"
#endif

/*! oszlopelválasztó karakter, alapértelmezésben "," */
#ifndef PMATRIX_OSZLOP_ELVALASZTO
#define PMATRIX_OSZLOP_ELVALASZTO ","
#endif

/*! a mtrx fájlok fejlécét elválasztó karakter, alapértelmezésben "_" */
#ifndef PMATRIX_FEJLEC_ELVALASZTO
#define PMATRIX_FEJLEC_ELVALASZTO "_"
#endif

/*! az írási-olvasási buffer mérete */
#ifndef PMATRIX_BUFFER_MERET
#define PMATRIX_BUFFER_MERET 2048
#endif





