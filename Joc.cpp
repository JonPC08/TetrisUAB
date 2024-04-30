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
    string linea;
    if (fitxer.is_open()) 
    {   
        string linea;
        fitxer >> linea;
        for (int i = 0; i < 4; i++)
            m_seguentsFigures[i] = stoi(linea);
        int a = 0;
        while(fitxer.eof()) 
        {
            fitxer >> linea;
            for (int b = 0; b < MAX_COL; b++)
                m_tauler.setCasella(stoi(linea), a, b);
            a++;
        }
        fitxer.close();
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

int Joc::baixaFigura()
{
    Figura figuraAntes;
    int dimMatriu = m_figura[n_m_figura].getDimMatriu();
    int matriuFigura[dimMatriu][dimMatriu];
    int liniesCompletades = 0;
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            matriuFigura[a][b] =  m_figura[n_m_figura].getMatriuFigura(a, b);
            
        }
    }
    m_figura[n_m_figura].increasePosicioFiguraX();
    bool colisiona = colisioFigura(matriuFigura, dimMatriu);
    if (colisiona)
    {
        m_figura[n_m_figura].decreasePosicioFiguraX();
        int listaFilasCompletas[MAX_FILA];
        for (int i = 0; i < MAX_FILA; i++) {
            listaFilasCompletas[i] = -1;
        }
        bool continuar_linea;
        int numeroFilasCompletas = 0;
        for (int a = 0; a < MAX_FILA; a++) {
            continuar_linea = true;
            int b = 0;
            while ((continuar_linea == true) && (b < MAX_COL)) {
                if (m_tauler.getCasella(a, b) == 0)
                {
                    continuar_linea = false;
                    b = 0;
                }
                else
                {
                    b++;
                }
            }
            if (continuar_linea) {
                listaFilasCompletas[numeroFilasCompletas] = a;
                numeroFilasCompletas++;
            }
        }

        // en la lista filas completas estaran todas las filas que hay que eliminar

        n_m_figura++;

        //añadir figura a matriz general
        //recorrer matriz general mirando las 8 filas para ver cuales se han completado
        //una vez sepamos cuantas se han completado asignamos guardamos las lineas completadas en un array para saber cuales se han completado y igualamos lineascompletadas = a esse numero
        //liniesCompletades = x;
        //ahora gracias al array anteriormente creado localizamos dicha posicion de la fila y bajamos toas las superiores una posicion hasta que el array se acabe (podemos inicializar el array array[8] como -1 para saber cuando se han acabado)
        //hacer n_m_figura++
    }
    else
    {

    }
    return liniesCompletades;
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
                    bool colisiona = true;
                }
                else
                {
                    if (m_tauler.getCasella(m_figura[n_m_figura].getPosicioFiguraX() + a, m_figura[n_m_figura].getPosicioFiguraY() + b) != 0) 
                    {
                        bool colisiona = true;
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