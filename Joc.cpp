#include "Joc.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
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
        for (int i = 0; i < arraySize(m_seguentsFigures); i++) // QUITAR
            fitxer << m_seguentsFigures[i] << " "; // QUITAR
        for (int a = 0; a < MAX_FILA; a++)
        {
            fitxer << endl;
            for (int b = 0; b < MAX_COL; b++)
                fitxer << m_tauler.getCasella(a, b) << " ";
        }
        fitxer.close();
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