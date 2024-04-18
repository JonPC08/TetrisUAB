#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
    Tauler();
private:
    int m_tauler[MAX_FILA][MAX_COL];

};
#endif


/* Diseño del tablero:

(0,0)
 -1  0  0  0  0  0  0 -1
 -1  0  0  0  0  0  0 -1
 -1  0  0  0  0  0  0 -1
 -1  0  0  0  0  0  0 -1
 -1  0  0  0  0  0  0 -1
 -1  0  0  0  0  0  0 -1
 -1  0  0  0  0  0  0 -1
 -1 -1 -1 -1 -1 -1 -1 -1
                     (8,8)

*/ 