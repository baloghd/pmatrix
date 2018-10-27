# pmatrix
(PROG1 NHF)

A pmatrix egy mátrix függvénykönyvtár C nyelven. Használatával tetszőleges méretű mátrixok hozhatók létre (sztringből vagy textfájlból) és rajtuk műveletek végezhetők, ezek természetesen a műveletnek megfelelő mátrixot adják vissza. A mátrixok fájlba írhatóak, velük további számítások végezhetőek. 

### használata
A modularitást szem előtt tartva pmatrix több fejlécből épül fel. Ezek:
- *Matrix.h*: a könyvtár alapját képező Matrix struktúrát és létrehozását írja le
- *Matrix_IO.h*: a Matrix struktúrák beolvasását, kiírását leíró függvények
- *Matrix_muveletek.h*: a Matrixokon végrehajtható műveleteket tárolja


