/*! \file */ 

//általános
/*! a pmatrix verziószám */
#define PMATRIX_VERZIOSZAM "1"
/*! a pmatrix alverziószám */
#define PMATRIX_ALVERZIOSZAM "0"

#define PMATRIX_VERZIO PMATRIX_VERZIOSZAM "." PMATRIX_ALVERZIOSZAM

/*! tizedes precízió a standard kimenetre való írásnál */
#define PMATRIX_TIZEDES_PRECIZIO_KIIRAS 3
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

/*! az írási-olvasási buffer mérete */
#ifndef PMATRIX_BUFFER_MERET
#define PMATRIX_BUFFER_MERET 4096
#endif





