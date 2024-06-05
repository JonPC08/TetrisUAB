#include "Tauler.h"
#include "GraphicManager.h"
#include "Partida.h"
#include <iostream>


Tauler::Tauler()
{
    // Inicializamos todas las casillas del tablero a 0
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            m_tauler[i][j] = 0;
    }
}


void Tauler::setCasella(const int numero, const int a, const int b)
{
    m_tauler[a][b] = numero;
}


void Tauler::dibuixa() 
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            if (getCasella(i, j) != 0)
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_NAME(getCasella(i, j) + 1),
                    POS_X_TAULER + ((j + 1) * MIDA_QUADRAT),
                    POS_Y_TAULER + ((i + 1 - 1) * MIDA_QUADRAT), false);
            }
        }
    }
}