# pmatrix
(PROG1 NHF)

A pmatrix egy mátrix függvénykönyvtár C nyelven. Használatával tetszőleges méretű mátrixok hozhatók létre (sztringből vagy textfájlból) és rajtuk műveletek végezhetők, ezek természetesen a műveletnek megfelelő mátrixot adják vissza. A mátrixok fájlba írhatóak, velük további számítások végezhetőek. 

### használata
A modularitást szem előtt tartva pmatrix több fejlécből épül fel. Ezek:
- *Matrix.h*: a könyvtár alapját képező Matrix struktúrát, létrehozását és a dinamikus memória kezelését leíró függvényeket tartalmazza
- *Matrix_IO.h*: a Matrix struktúrák beolvasását, kiírását leíró függvények
  - a be- és kimeneti fájlformátum tetszőleges elválasztókarakterrel használható, alapértelmezésben pontosvessző
  - a be- és kimenet lényegében fejléc nélküli csv fájl
  - a sztring kimenet alapértelmezésben kompatibilis a Matlab/Octave formátummal
    - pl. a 2x2-es identitásmátrix = [1, 0; 0,1]
- *Matrix_muveletek.h*: a Matrixokon végrehajtható műveleteket tárolja
  - ezek is modulárisan épülnek fel, tehát pl. a Gauss-elimináció segédfüggvényeket használ a sorok cseréjére vagy szorzására (ezek önmagukban is használhatóak, ha az alkalmazás megkívánja)
  - lineáris függetlenség meghatározása
  - Gauss-elimináció
  - invertálás
  - rang
  - megfelelő méretű mátrixoknál determináns számítása
  


