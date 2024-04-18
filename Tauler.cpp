#include "Tauler.h"


Tauler::Tauler()
{
    // Inicializamos todas las casillas del tablero a 0
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            m_tauler[i][j] = 0;
    }
}

void Tauler::setCasella(const int numero, const int x, const int y)
{
    m_tauler[x][y] = numero;
}