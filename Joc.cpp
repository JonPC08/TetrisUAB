#include "Joc.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
    n_m_figura = 0;
    for (int i = 0; i < MAX_FIGURES; i++) 
    {
        m_seguentsFigures[i] = -1;
    }
    ifstream fitxer;
    fitxer.open(nomFitxer);
    int caracter;
        if (fitxer.is_open()) 
    {   
        for (int i = 0; i < 4; i++)
        {
            fitxer >> caracter;
            m_seguentsFigures[i] = caracter;
        }
        int a = 0;
        while(!(fitxer.eof()))
        {
            for (int b = 0; b < MAX_COL; b++)
            {
                fitxer >> caracter;
                m_tauler.setCasella(caracter, a, b);
            }
            a++;
        }
        fitxer.close();
        for (int i = 0; i < 4; i++) {
            ColorFigura color; 
            TipusFigura tipus;
            switch (m_seguentsFigures[i])
            
            {
                case 0:
                    color = COLOR_NEGRE;
                    tipus = NO_FIGURA;
                    break;
                case 1:
                    color = COLOR_GROC;
                    tipus = FIGURA_O;
                    break;
                case 2:
                    color = COLOR_BLAUCEL;
                    tipus = FIGURA_I;
                    break;
                case 3:
                    color = COLOR_MAGENTA;
                    tipus = FIGURA_T;
                    break;
                case 4:
                    color = COLOR_TARONJA;
                    tipus = FIGURA_L;
                    break;
                case 5:
                    color = COLOR_BLAUFOSC;
                    tipus = FIGURA_J;
                    break;
                case 6:
                    color = COLOR_VERMELL;
                    tipus = FIGURA_Z;
                    break;
                case 7:
                    color = COLOR_VERD;
                    tipus = FIGURA_S;
                    break;
                default:
                    color = NO_COLOR;
                    tipus = NO_FIGURA;
                    break;
                }
            m_figura[i] = Figura(color, tipus, 0, 0);
        }
    }
}

void Joc::escriuTauler(const string& nomFitxer) 
{
    ofstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open()) 
    {   
        string linea;
        for (int a = 0; a < MAX_FILA; a++)
        {
            for (int b = 0; b < MAX_COL; b++)
                fitxer << m_tauler.getCasella(a, b) << " ";
            fitxer << endl;
        }
        fitxer.close();
    }
}

bool Joc::giraFigura(DireccioGir direccio)
{
    int dimMatriu = m_figura[n_m_figura].getDimMatriu();
    int matriuFigura[dimMatriu][dimMatriu];
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            matriuFigura[a][b] =  m_figura[n_m_figura].getMatriuFigura(a, b);
        }
    }
    int aux;
    if (direccio == GIR_HORARI)
    {
        // Trasposta
        for (int a = 0; a < dimMatriu; a++) 
        {
            for (int b = a; b < dimMatriu; b++) // En fer això, només fem iteracions en el triangle superior dret de la matriu
            {
                aux = matriuFigura[a][b];
                matriuFigura[a][b] = matriuFigura[b][a];
                matriuFigura[b][a] = aux;
            }
        }
        // Invertir columnes
        if (dimMatriu % 2 == 0) // Si es parell
        {
            for (int a = 0; a < dimMatriu; a++)
            {
                for (int b = 0; b < int(dimMatriu / 2); b++)
                {
                    aux = matriuFigura[a][b];
                    matriuFigura[a][b] = matriuFigura[a][dimMatriu - b - 1];
                    matriuFigura[a][dimMatriu - b - 1] = aux;
                }
            }
        }
        else // Si es senar
        {
            for (int a = 0; a < dimMatriu; a++) 
            {
                for (int b = 0; b < int(dimMatriu / 2); b++) 
                {
                    aux = matriuFigura[a][b];
                    matriuFigura[a][b] = matriuFigura[a][dimMatriu - b - 1];
                    matriuFigura[a][dimMatriu - b - 1] = aux;
                }
            }
        }
    }
    else // if (direccio == GIR_ANTI_HORARI)
    {
        // Trasposta
        for (int a = 0; a < dimMatriu; a++) 
        {
            for (int b = a; b < dimMatriu; b++)
            {
                aux = matriuFigura[a][b];
                matriuFigura[a][b] = matriuFigura[b][a];
                matriuFigura[b][a] = aux;
            }
        }
        // Invertir files
        if (dimMatriu % 2 == 0) // Si es parell
        {
            for (int a = 0; a < int(dimMatriu / 2); a++) 
            {
                for (int b = 0; b < dimMatriu; b++)
                {
                    aux = matriuFigura[a][b];
                    matriuFigura[a][b] = matriuFigura[dimMatriu - a - 1][dimMatriu];
                    matriuFigura[dimMatriu - a - 1][dimMatriu] = aux;
                }
            }
        }
        else // Si es senar
        {
            for (int a = 0; a < int(dimMatriu / 2); a++) 
            {
                for (int b = 0; b < dimMatriu; b++) 
                {
                    aux = matriuFigura[a][b];
                    matriuFigura[a][b] = matriuFigura[a][dimMatriu - b - 1];
                    matriuFigura[a][dimMatriu - b - 1] = aux;
                }
            }
        }
    }
    // Actualizamos valores
    bool colisiona = colisioFigura(matriuFigura, dimMatriu);
    if (colisiona == false) 
    {
        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                m_figura[n_m_figura].setMatriuFigura(a, b, matriuFigura[a][b]);
            }
        }
    }
    return !colisiona;
}

bool Joc::mouFigura(int dirX)
{
    Figura figuraAntes;
    figuraAntes.setPosicioFiguraX(m_figura[n_m_figura].getPosicioFiguraX());
    figuraAntes.setPosicioFiguraY(m_figura[n_m_figura].getPosicioFiguraY());
    int const dimMatriu = m_figura[n_m_figura].getDimMatriu();
    int matriuFigura[dimMatriu][dimMatriu];
    
    bool movimentValid = true;
    // J: Caragamos la figura tal como era antes en figuraAntes
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            figuraAntes.setMatriuFigura(a, b, m_figura[n_m_figura].getMatriuFigura(a, b));
        }
    }
    // Hacia la derecha (+1 en eje Y)
    if (dirX == 1)
    {
        // Comprovamos colision
        m_figura[n_m_figura].increasePosicioFiguraY();
        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                matriuFigura[a][b] =  m_figura[n_m_figura].getMatriuFigura(a, b);
            }
        }
        bool colisiona = colisioFigura(matriuFigura, dimMatriu);
        // Si colisiona
        if (colisiona)
        {
            m_figura[n_m_figura].decreasePosicioFiguraY();
            // Como colisiona devolvemos la figura a su posicion y devolvemos false en la funcion
            movimentValid = false;
        }
        else
        {
            // Añadir figura a matriz general
            movimentValid = true;
            actualitzarTauler(figuraAntes, m_figura[n_m_figura]);
        }
    }
    // Hacia la izquierda (-1 en eje Y)
    else if (dirX == -1)
    {
        // Comprovamos colision
        m_figura[n_m_figura].decreasePosicioFiguraY();
        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                matriuFigura[a][b] =  m_figura[n_m_figura].getMatriuFigura(a, b);
            }
        }
        bool colisiona = colisioFigura(matriuFigura, dimMatriu);
        // Si colisiona
        if (colisiona)
        {
            m_figura[n_m_figura].increasePosicioFiguraY();
            // Como colisiona devolvemos la figura a su posicion y devolvemos false en la funcion
            movimentValid = false;
        }
        else
        {
            // Añadir figura a matriz general
            movimentValid = true;
            actualitzarTauler(figuraAntes, m_figura[n_m_figura]);
        }
    }
    return movimentValid;
}

int Joc::baixaFigura()
{
    Figura figuraAntes;
    figuraAntes.setPosicioFiguraX(m_figura[n_m_figura].getPosicioFiguraX());
    figuraAntes.setPosicioFiguraY(m_figura[n_m_figura].getPosicioFiguraY());
    int dimMatriu = m_figura[n_m_figura].getDimMatriu();
    int matriuFigura[dimMatriu][dimMatriu];
    int numeroFilasCompletas = 0;
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            figuraAntes.setMatriuFigura(a, b, m_figura[n_m_figura].getMatriuFigura(a, b));
        }
    }
    m_figura[n_m_figura].increasePosicioFiguraX();
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            matriuFigura[a][b] =  m_figura[n_m_figura].getMatriuFigura(a, b);
        }
    }
    bool colisiona = colisioFigura(matriuFigura, dimMatriu);
    if (colisiona)
    {
        m_figura[n_m_figura].decreasePosicioFiguraX();
        // M: Recorrer matriz general mirando las 8 filas para ver cuales se han completado
        int listaFilasCompletas[MAX_FILA];
        for (int i = 0; i < MAX_FILA; i++) 
        {
            listaFilasCompletas[i] = -1;
        }
        bool continuar_linea;
        int numeroFilasCompletas = 0;
        for (int a = 0; a < MAX_FILA; a++) 
        {
            continuar_linea = true;
            int b = 0;
            while ((continuar_linea == true) && (b < MAX_COL)) 
            {
                if (m_tauler.getCasella(a, b) == 0)
                {
                    continuar_linea = false;
                }
                else
                {
                    b++;
                }
            }
            if (continuar_linea) 
            {
                listaFilasCompletas[numeroFilasCompletas] = a;
                numeroFilasCompletas++;
            }
        }
        // M: En la lista filas completas estaran todas las filas que hay que eliminar
        bool continuarListaFilasCompletas = true;
        int a = 0;
        while ((a < numeroFilasCompletas) && (continuarListaFilasCompletas == true))
        {
            int b = 0;
            while ((b < MAX_COL) && (continuarListaFilasCompletas == true))
            {
                if ((listaFilasCompletas[a]) != -1) 
                {
                    m_tauler.setCasella(0, listaFilasCompletas[a], b);
                    b++;
                }
                else
                {
                    continuarListaFilasCompletas = false;
                }
            }
            a++;
        }
        // Cas de flila 2 a 8, la fila 1 no cal tenirla en compte
        for (int a = 1; a < MAX_FILA; a++)
        {
            bool filaBuida = true;
            int b = 0;
            while ((b < MAX_COL) && (filaBuida == true))
            {
                if (m_tauler.getCasella(a, b) != 0)
                {
                    filaBuida = false;
                }
                else {
                    b++;
                }
            }
            if (filaBuida) {
                for (int i = a; i > 0; i--)
                {
                    for (int j = 0; j < MAX_COL; j++) 
                    {
                        m_tauler.setCasella(m_tauler.getCasella(i - 1, j), i, j);
                    }
                }
                for (int i = 0; i < MAX_COL; i++)
                {
                    m_tauler.setCasella(0, 0, i);
                }
            }
        }
        // M: Hacer n_m_figura++
        n_m_figura++;
    }
    else
    {
        actualitzarTauler(figuraAntes, m_figura[n_m_figura]);
    }
    return numeroFilasCompletas;
}

void Joc::actualitzarTauler(Figura figuraAntes, Figura figuraAhora)
{
    // Elminiacion Figura Anterior
    int posicionFiguraAntesX = figuraAntes.getPosicioFiguraX();
    int posicionFiguraAntesY = figuraAntes.getPosicioFiguraY();

    for (int a = 0; a < figuraAntes.getDimMatriu(); a++)
    {
        for (int b = 0; b < figuraAntes.getDimMatriu(); b++)
        {
            if ((a + posicionFiguraAntesX >= 0) && (a + posicionFiguraAntesX <= MAX_FILA - 1) && (b + posicionFiguraAntesY >= 0) && (b + posicionFiguraAntesY <= MAX_COL)) 
            {
                if (figuraAntes.getMatriuFigura(a, b) != 0)
                {
                    m_tauler.setCasella(0, a + posicionFiguraAntesX, b + posicionFiguraAntesY);
                }
            }
        }
    }
    // Actualización Figura Ahora
    int posicionFiguraAhoraX = figuraAhora.getPosicioFiguraX();
    int posicionFiguraAhoraY = figuraAhora.getPosicioFiguraY();

    for (int a = 0; a < figuraAhora.getDimMatriu(); a++)
    {
        for (int b = 0; b < figuraAhora.getDimMatriu(); b++)
        {
            if ((a + posicionFiguraAhoraX >= 0) && (a + posicionFiguraAhoraX <= MAX_FILA - 1) && (b + posicionFiguraAhoraY >= 0) && (b + posicionFiguraAhoraY <= MAX_COL)) 
            {
                if (figuraAntes.getMatriuFigura(a, b) != 0)
                {
                    m_tauler.setCasella(figuraAhora.getTipusFigura(), a + posicionFiguraAhoraX, b + posicionFiguraAhoraY);
                }
            }
        }
    }
}

bool Joc::colisioFigura(int matriuFigura[][MAX_DIM], int dim)
{
    bool colisiona = false;
    int a = 0;
    int b = 0;
    while ((a < dim) && (colisiona == false))
    {
        while ((b < dim) && (colisiona == false))
        {
            if (matriuFigura[a][b] != 0) 
            {       
                if (((m_figura[n_m_figura].getPosicioFiguraY() + b) < 0) || ((m_figura[n_m_figura].getPosicioFiguraY() + b) > MAX_COL - 1) || ((m_figura[n_m_figura].getPosicioFiguraX() + a) > MAX_FILA - 1))
                {
                    colisiona = true;
                }
                else
                {
                    if (m_tauler.getCasella(m_figura[n_m_figura].getPosicioFiguraX() + a, m_figura[n_m_figura].getPosicioFiguraY() + b) != 0) 
                    {
                        colisiona = true;
                    }
                }
            }
            b++;
        }
        a++;
    }
    return colisiona;
}

int arraySize(int array[MAX_FIGURES]) 
{
    bool acabar = false;
    int i = 0;
    while(!acabar) 
    {
        if (array[i] == -1) 
            acabar = true;
        else
            i++;
    }
    return i;
}