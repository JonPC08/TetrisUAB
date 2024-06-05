#include "Figura.h"
#include "GraphicManager.h"
#include "Partida.h"


Figura::Figura()
{
    m_colorFigura = NO_COLOR;
    m_tipusFigura = NO_FIGURA;
    for (int a = 0; a < MAX_DIM; a++) 
    {
        for (int b = 0; b < MAX_DIM; b++) 
        {
            m_matriuFigura[a][b] = 0;
        }
    }
    m_dimMatriu = 0;
    m_posicioFigura[0] = 0;
    m_posicioFigura[1] = 0;
};


Figura::Figura(const ColorFigura colorFigura, const TipusFigura tipusFigura, const int x, const int y)
{
    m_colorFigura = colorFigura;
    m_tipusFigura = tipusFigura;
    for (int a = 0; a < MAX_DIM; a++) 
    {
        for (int b = 0; b < MAX_DIM; b++) 
        {
            m_matriuFigura[a][b] = 0;
        }
    }
    inicialitzaForma(tipusFigura);
    m_posicioFigura[0] = x;
    m_posicioFigura[1] = y;
};


void Figura::inicialitza(TipusFigura tipusFigura, int fila, int columna)
{
    m_tipusFigura = tipusFigura;
    m_posicioFigura[0] = fila;
    m_posicioFigura[1] = columna;
    inicialitzaForma(tipusFigura);
}


void Figura::dibuixa(int x, int y)
{
    int compensacionX = 1;
    int compensacionY = 1;
    int dimMatriu = getDimMatriu();
    int matriuFigura[MAX_DIM][MAX_DIM];
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            if (getMatriuFigura(a, b) != 0) 
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_NAME(getTipusFigura() + 1),
                    POS_X_TAULER + ((y + compensacionY + b) * MIDA_QUADRAT),
                    POS_Y_TAULER + ((x + compensacionX - 1 + a) * MIDA_QUADRAT), false);
            }
        }
    }
}


void Figura::inicialitzaForma(TipusFigura tipusFigura)
{
    switch (tipusFigura)
    {
        case FIGURA_O:
            m_dimMatriu = 2;
            m_matriuFigura[0][0] = 1;
            m_matriuFigura[0][1] = 1;
            m_matriuFigura[1][0] = 1;
            m_matriuFigura[1][1] = 1;
            break;
        case FIGURA_I:
            m_dimMatriu = 4;
            m_matriuFigura[1][0] = 2;
            m_matriuFigura[1][1] = 2;
            m_matriuFigura[1][2] = 2;
            m_matriuFigura[1][3] = 2;
            break;
        case FIGURA_T:
            m_dimMatriu = 3;
            m_matriuFigura[0][1] = 3;
            m_matriuFigura[1][0] = 3;
            m_matriuFigura[1][1] = 3;
            m_matriuFigura[1][2] = 3;
            break;
        case FIGURA_L:
            m_dimMatriu = 3;
            m_matriuFigura[0][2] = 4;
            m_matriuFigura[1][0] = 4;
            m_matriuFigura[1][1] = 4;
            m_matriuFigura[1][2] = 4;
            break;
        case FIGURA_J:
            m_dimMatriu = 3;
            m_matriuFigura[0][0] = 5;
            m_matriuFigura[1][0] = 5;
            m_matriuFigura[1][1] = 5;
            m_matriuFigura[1][2] = 5;
            break;
        case FIGURA_Z:
            m_dimMatriu = 3;
            m_matriuFigura[0][0] = 6;
            m_matriuFigura[0][1] = 6;
            m_matriuFigura[1][1] = 6;
            m_matriuFigura[1][2] = 6;
            break;
        case FIGURA_S:
            m_dimMatriu = 3;
            m_matriuFigura[0][1] = 7;
            m_matriuFigura[0][2] = 7;
            m_matriuFigura[1][0] = 7;
            m_matriuFigura[1][1] = 7;
            break;
    }
}


void Figura::setPosicioFiguraX(const int x) 
{
    m_posicioFigura[0] = x;
};


void Figura::setPosicioFiguraY(const int y) 
{
    m_posicioFigura[1] = y;
};


// Decrementar x, moure abaix (fila)
void Figura::decreasePosicioFiguraX()
{
    m_posicioFigura[0]--;
};


// Incrementar x, moure cap adalt (fila)
void Figura::increasePosicioFiguraX()
{
    m_posicioFigura[0]++;
};


// Decrementar y, moure a la esquerra (columna)
void Figura::decreasePosicioFiguraY()
{
    m_posicioFigura[1]--;
};


// Incrementar y, moure a la dreta (columna)
void Figura::increasePosicioFiguraY()
{
    m_posicioFigura[1]++;
};


void Figura::setMatriuFigura(const int a, const int b, const int valor) 
{
    m_matriuFigura[a][b] = valor;
};


void Figura::setDimMatriu(const int dim)
{
    m_dimMatriu = dim;
};


void Figura::setTipusFigura(const int tipus)
{
    m_tipusFigura = TipusFigura(tipus);
}