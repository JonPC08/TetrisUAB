#include "Joc.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    string linea;
    string lineaPartida;
    if (fitxer.is_open()) 
    {   
        string palabra;
        fitxer >> m_seguentsFigures[0] >> m_seguentsFigures[1] >> m_seguentsFigures[2] >> m_seguentsFigures[3];
        int a = 0;
        while(fitxer.eof()) 
        {
            fitxer >> palabra;
            for (size_t b = 0; b < MAX_COL; b++)
            {
                m_tauler.setCasella(stoi(palabra), a, b);
            }
            a++;
        }

        fitxer.close();
    }
}