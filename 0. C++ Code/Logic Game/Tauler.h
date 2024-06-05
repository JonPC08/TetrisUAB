#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"


const int MAX_FILA = 21;
const int MAX_COL = 11;


class Tauler
{
    public:
        Tauler();
        // Setters
        void setCasella(const int numero, const int x, const int y);
        // Getters
        int getCasella(const int a, const int b) const {return m_tauler[a][b];};
        // Metodes
        void dibuixa();
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

[En parte 2 ha cambiado el tamaño]

*/ 