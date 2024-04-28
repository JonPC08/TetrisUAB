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
