#include "Tauler.h"


Tauler::Tauler()
{// Inicializamos todas las casillas del tablero a 0
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            m_tauler[i][j] = 0;
        }
    }
    // Inicializamos el borde del tablero a -1
    for (int i = 0; i < MAX_FILA; i++) {
        m_tauler[0][i] = -1;
        m_tauler[MAX_COL][i] = -1;
    }
    for (int i = 1; i < MAX_COL - 1; i++) {
        m_tauler[i][MAX_FILA] = -1;
    }   

    /*
    [PREGUNTAR SI MEJOR HAGO ESTO PORQUE CREO QUE DE ESTA FORMA SE AHORRAN CICLOS PERO ES MAS DIFICIL DE ENTENDER];
    for (int i = 0; i < 8; i++) { // DONDE 8 PUEDE SER TANTO O MAX_FILA O MAX_COL
        m_tauler[0][i] = -1;
        m_tauler[MAX_COL][i] = -1;
        m_tauler[i][MAX_FILA] = -1;
    }
    */

};