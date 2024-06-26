#include "Figura.h"

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
    switch (m_tipusFigura)
    {
        case FIGURA_O:
            m_dimMatriu = 2;
            m_matriuFigura[0][0] = 1;
            m_matriuFigura[0][1] = 1;
            m_matriuFigura[1][0] = 1;
            m_matriuFigura[1][1] = 1;
            break;
            
            /*

            1  1
            1  1

            */

        case FIGURA_I:
            m_dimMatriu = 4;
            m_matriuFigura[1][0] = 2;
            m_matriuFigura[1][1] = 2;
            m_matriuFigura[1][2] = 2;
            m_matriuFigura[1][3] = 2;
            break;

            /*

            0  0  0  0
            2  2  2  2
            0  0  0  0
            0  0  0  0
            
            */
           
        case FIGURA_T:
            m_dimMatriu = 3;
            m_matriuFigura[0][1] = 3;
            m_matriuFigura[1][0] = 3;
            m_matriuFigura[1][1] = 3;
            m_matriuFigura[1][2] = 3;
            break;

            /*

            0  3  0 
            3  3  3 
            0  0  0  
            
            */
            
        case FIGURA_L:
            m_dimMatriu = 3;
            m_matriuFigura[0][2] = 4;
            m_matriuFigura[1][0] = 4;
            m_matriuFigura[1][1] = 4;
            m_matriuFigura[1][2] = 4;
            break;
            
            /*

            0  0  4  
            4  4  4 
            0  0  0  
            
            */

        case FIGURA_J:
            m_dimMatriu = 3;
            m_matriuFigura[0][0] = 5;
            m_matriuFigura[1][0] = 5;
            m_matriuFigura[1][1] = 5;
            m_matriuFigura[1][2] = 5;
            break;
            
            /*

            5  0  0  
            5  5  5 
            0  0  0  
            
            */
            
        case FIGURA_Z:
            m_dimMatriu = 3;
            m_matriuFigura[0][0] = 6;
            m_matriuFigura[0][1] = 6;
            m_matriuFigura[1][1] = 6;
            m_matriuFigura[1][2] = 6;
            break;

            /*

            6  6  0  
            0  6  6 
            0  0  0  
            
            */
            
        case FIGURA_S:
            m_dimMatriu = 3;
            m_matriuFigura[0][1] = 7;
            m_matriuFigura[0][2] = 7;
            m_matriuFigura[1][0] = 7;
            m_matriuFigura[1][1] = 7;
            break;

            /*

            0  7  7  
            7  7  0 
            0  0  0  
            
            */
           
    }
    m_posicioFigura[0] = x;
    m_posicioFigura[1] = y;
};

void Figura::setPosicioFiguraX(const int x) 
{
    m_posicioFigura[0] = x;
};

void Figura::setPosicioFiguraY(const int y) 
{
    m_posicioFigura[1] = y;
};

// Decrementar x, moure abaix

void Figura::decreasePosicioFiguraX()
{
    m_posicioFigura[0]--;
};

// Incrementar x, moure a la dreta
void Figura::increasePosicioFiguraX()
{
    m_posicioFigura[0]++;
};

// Decrementar y, moure a la esquerra
void Figura::decreasePosicioFiguraY()
{
    m_posicioFigura[1]--;
};

// Incrementar y, moure a la dreta
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