#include "Figura.h"

Figura::Figura()
{
    m_colorFigura = NO_COLOR;
    m_tipusFigura = NO_FIGURA;
    m_posicioFigura[0] = 0;
    m_posicioFigura[1] = 0;
    m_formaActualFigura = 0; 
};

Figura::Figura(const ColorFigura colorFigura, const TipusFigura tipusFigura, const int x, const int y, const int formaFigura)
{
    m_colorFigura = colorFigura;
    m_tipusFigura = tipusFigura;
    m_posicioFigura[0] = x;
    m_posicioFigura[1] = y;
    m_formaActualFigura = formaFigura; 
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

// Si direccio = 0 girar a la dreta, Si direccio = 1 girar a la esquerra.
void Figura::setFormaActualFigura(const int direccio)
{   
    if (direccio == 0)
        m_formaActualFigura = (m_formaActualFigura + (direccio)) % 4;
    else
        m_formaActualFigura = (m_formaActualFigura - (direccio)) % 4;
};