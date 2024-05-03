#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
    Tauler();
    void inicialitzaTauler();

    // Setters
    void setCasella(const int numero, const int x, const int y);

    // Getters
    int getCasella(const int a, const int b) const {return m_tauler[a][b];};

private:
    int m_tauler[MAX_FILA][MAX_COL];

};
#endif

/* Diseño del tablero:

(0,0)
  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0
                     (7,7)

*/ 