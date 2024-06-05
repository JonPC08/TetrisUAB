#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "GraphicManager.h"
#include "Joc.h"

#include <fstream>

using namespace std;

const int MAX_ELEMENTS = 1000;

struct NodeTipusMoviment {
};

struct NodeFigura {
};


class Partida
{
    public:
        Partida();
        int randomizer(int a, int b);
        void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
        void actualitza(int mode, double deltaTime);
        bool acaba() const { return m_acabar; };
        int getNivellActual() const { return m_nivell; };
        int getPuntuacio() const { return m_puntuacio; };
        void creaFigura(ColorFigura color, TipusFigura tipus, int x, int y); // Nueva para crear la figura desde partida y cuando cambiemos a una nueva lo llamamos
        void setDificultat(); // Canvia m_nivellActual y m_velocitatJoc
        bool seguentFigura(int mode); // Comprovamos si tenemos que cargar a la siguiente figura
        Joc& getJoc() { return m_joc; }; // Para devolver Joc
        bool partidaAcabada(int mode); // Comprovador de si ha acabado la partida, ha sobrepasado el limite superior
        bool getm_acabar() { return m_acabar; };
        string getnomJugador() { return m_nomJugador; };
        void guardarMovimentsAuto(const string& fitxerMoviments);
        void guardarFiguresAuto(const string& fitxerFigures);
    private:
        double m_temps;
        double m_velocitatJoc;
        int m_nivell;
        int m_puntuacio;
        string m_nomJugador;
        bool m_acabar;
        Joc m_joc;
        int m_moviments[MAX_ELEMENTS];
        int m_figures[MAX_ELEMENTS][4];
        int m_n_moviments;
        int m_n_figures;
        int index_m_moviments;
        int index_m_figures;
};



#endif