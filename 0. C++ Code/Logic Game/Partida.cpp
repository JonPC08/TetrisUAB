#include "Partida.h"
#include <random> // No se si esta permitido pero no hay otra forma (encima va fatal la libreria)
#include <iostream>


using std::cout;


Partida::Partida()
{
    m_nivell = 0;
    m_puntuacio = 0;
    m_temps = 0;
    m_acabar = false;
    m_velocitatJoc = 1;
}


int Partida::randomizer(int a, int b)
{
    // Seguent figura aleatoria
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(a, b);
    int resultado = distr(gen);
    return resultado;
}


void Partida::inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{   
    if (mode == 0)
    {
        int tipus_random = randomizer(1, 7);
        int tipus = tipus_random;
        int columna_random = randomizer(1, 11 - 1 - m_joc.getFigura().getDimMatriu());
        int columna = columna_random;
        int gir_random = randomizer(0, 3);
        int gir = gir_random;
        creaFigura(ColorFigura(tipus), TipusFigura(tipus), 1, columna);
        m_joc.giraFiguraInicial(GIR_HORARI, gir);
    }
    else if (mode == 1)
    { 
        m_n_moviments = 0;
        m_n_figures = 0;
        index_m_moviments = 0;
        index_m_figures = 0;
        for (int a = 0; a < MAX_ELEMENTS; a++) {
            m_moviments[a] = -1;
            for (int b = 0; b < 4; b++)
            {
                m_figures[a][b] = -1;
            }
        }
        int tipus, fila, columna, gir, color;
        ifstream fitxer;
        fitxer.open(fitxerInicial);
        if (fitxer.is_open())
        {
            fitxer >> tipus >> fila >> columna >> gir;
            ColorFigura taulerInicial[MAX_FILA][MAX_COL];
            for (int i = 0; i < MAX_FILA; i++)
            {
                for (int j = 0; j < MAX_COL; j++)
                {
                    fitxer >> color;
                    m_joc.getTauler().setCasella(color, i, j);
                }
            }
        }
        fitxer.close();
        creaFigura(ColorFigura(tipus), TipusFigura(tipus), fila, columna);
        m_joc.giraFiguraInicial(GIR_HORARI, gir);
        guardarMovimentsAuto(fitxerMoviments);
        guardarFiguresAuto(fitxerFigures);
    }
    else 
    {
        // Output: Modo no existente, elije 0 o 1
    }
}


void Partida::guardarMovimentsAuto(const string& fitxerMoviments)
{
    ifstream fitxer;
    fitxer.open(fitxerMoviments);
    if (fitxer.is_open())
    {
        int tipus;
        while (!fitxer.eof())
        {
            fitxer >> tipus;
            m_moviments[m_n_moviments] = tipus;
            m_n_moviments++;
        }
    }
    fitxer.close();
}


void Partida::guardarFiguresAuto(const string& fitxerFigures)
{
    ifstream fitxer;
    fitxer.open(fitxerFigures);
    if (fitxer.is_open())
    {
        int fig, fil, col, gir;
        while (!fitxer.eof())
        {
            fitxer >> fig >> fil >> col >> gir;
            m_figures[m_n_figures][0] = fig;
            m_figures[m_n_figures][1] = fil;
            m_figures[m_n_figures][2] = col;
            m_figures[m_n_figures][3] = gir;
            m_n_figures++;
        }
    }
    fitxer.close();
}


void Partida::creaFigura(ColorFigura color, TipusFigura tipus, int x, int y)
{
    Figura figuraInicial = Figura(color, tipus, x - 1, y - 1);
    m_joc.setFigura(figuraInicial);
}


bool Partida::seguentFigura(int mode) 
{
    int dimMatriu = m_joc.getFigura().getDimMatriu();
    int matriuFigura[MAX_DIM][MAX_DIM];
    bool out = false;
    Tauler taulerNoFigura;
    // Copiamos Tablero
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {

            taulerNoFigura.setCasella(m_joc.getTauler().getCasella(i, j), i, j);
        }
    }
    // Ponemos 0 donde haya figura
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            if (m_joc.getFigura().getMatriuFigura(a, b) != 0)
            {
                taulerNoFigura.setCasella(0, m_joc.getFigura().getPosicioFiguraX() + a, m_joc.getFigura().getPosicioFiguraY() + b);
            }
        }
    }
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            if (m_joc.getFigura().getMatriuFigura(a, b) != 0) 
            {
                if ((m_joc.getFigura().getPosicioFiguraX() + a) > (MAX_FILA - (2)) || 
                    ((taulerNoFigura.getCasella(m_joc.getFigura().getPosicioFiguraX() + a + 1, m_joc.getFigura().getPosicioFiguraY() + b)) != 0))
                {
                    out = true;
                }
            }
        }
    }
    if (mode == 0)
    {
        if (out == true) 
        {
            int tipus_random = randomizer(1, 7);
            int tipus = tipus_random;
            int columna_random = randomizer(1, 11 - 1 - m_joc.getFigura().getDimMatriu());
            int columna = columna_random;
            int gir_random = randomizer(0, 3);
            int gir = gir_random;
            creaFigura(ColorFigura(tipus), TipusFigura(tipus), 1, columna);
            for (int i = 0; i < gir; i++)
            {
                m_joc.giraFigura(GIR_HORARI);
            }
            m_puntuacio += 10;
        }
        else
        {
            out = false;
        }
    }

    /*
    else if (mode == 1)
    {
        if (out == true)
        {
            int tipus = 1;

            int pos_Y = 1;

            creaFigura(ColorFigura(tipus), TipusFigura(tipus), 0, pos_Y); // Pos_Y deberia ser aleatoria
            m_puntuacio += 10;
        }
        else
        {
            out = false;
        }
    }
    */

    return out;
}


void Partida::setDificultat()
{
    m_velocitatJoc = 1.5 - (0.15 * m_nivell);
}


bool Partida::partidaAcabada(int mode)
{
    bool out = false;
    if (m_joc.getFigura().getPosicioFiguraX() < 1)
    {
        if (seguentFigura(mode) == true)
        {
            out = true;
        }
    }
    return out;
}


void Partida::actualitza(int mode, double deltaTime) 
{
    m_temps += deltaTime;
    m_acabar = false;
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);
    // Actualització del tauler
    m_joc.getTauler().dibuixa();
    // Imprimir coordenadas figura actual
    string coords = "Fila: " + to_string(m_joc.getFigura().getPosicioFiguraX()) + ", Columna: " + to_string(m_joc.getFigura().getPosicioFiguraY());
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 90, 1.0, coords);
    // Imprimir puntuación actual
    string points = "Punts: " + to_string(m_puntuacio);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 47, 1.0, points);
    // Impreión de nivel y aumento de dificultad 
    if ((m_puntuacio / 1000) > m_nivell) 
    {
        setDificultat();
        m_nivell++;
    }
    string level = "Nivell: " + to_string(m_nivell);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 225, POS_Y_TAULER - 47, 1.0, level);
    if (mode == 0) // Modo de juego manual
    {
        bool finalitzatFigura = false;
        int filesFetes = 0;
        int key = -1;
        if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT)) // Tecla pulsada
            key = KEYBOARD_RIGHT;
        else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
            key = KEYBOARD_LEFT;
        else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
            key = KEYBOARD_DOWN;
        else if (Keyboard_GetKeyTrg(KEYBOARD_UP))
            key = KEYBOARD_UP;
        else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
            key = KEYBOARD_SPACE;
        switch (key) // Ejecutamos movimiento
        {
        case KEYBOARD_RIGHT:
            m_joc.mouFigura(1);
            break;
        case KEYBOARD_LEFT:
            m_joc.mouFigura(-1);
            break;
        case KEYBOARD_DOWN:
            m_joc.giraFigura(GIR_ANTI_HORARI);
            break;
        case KEYBOARD_UP:
            m_joc.giraFigura(GIR_HORARI);
            break;
        case KEYBOARD_SPACE:
            int i = m_joc.getFigura().getPosicioFiguraX();
            while (i < MAX_FILA - 1)
            {
                int files = m_joc.baixaFigura();
                if (files > 0)
                {
                    m_puntuacio += 100 + (100 * 0.25 * files);
                }
                i++;
            }
            seguentFigura(mode);
            break;
        }
        if (m_temps > m_velocitatJoc)
        {
            if (m_joc.getFigura().getPosicioFiguraX() < N_FILES_TAULER)
            {
                int files = m_joc.baixaFigura();
                if (files > 0)
                {
                    m_puntuacio += 100 + (100 * 0.25 * files);
                }
            }
            m_temps = 0.0;
        }
        seguentFigura(mode);
        if (partidaAcabada(mode))
        {
            m_acabar = true;
        }
    }

    else if (mode == 1) {

        /*
        bool seguentBool = false;
        int files = -1;
        if (m_temps > 1)
        {
            switch (m_moviments[index_m_moviments]) // poner m_n_moviments para que en cada figura vuelva a empezar
            {
            case 0:
                m_joc.mouFigura(-1);
                break;
            case 1:
                m_joc.mouFigura(1);
                break;
            case 2:
                m_joc.giraFigura(GIR_HORARI);
                break;
            case 3:
                m_joc.giraFigura(GIR_ANTI_HORARI);
                break;
            case 4:
                files = m_joc.baixaFigura();
                if (files > 0)
                {
                    m_puntuacio += 100 + (100 * 0.25 * files);
                }
                seguentBool = seguentFigura(mode);
                if (seguentBool == true) {
                    index_m_figures++;
                }
                if (index_m_figures > m_n_figures)
                {
                    m_acabar = true;
                }
                break;
            case 5:
                int i = m_joc.getFigura().getPosicioFiguraX();
                while (i < MAX_FILA - 1)
                {
                    files = m_joc.baixaFigura();
                    if (files > 0)
                    {
                        m_puntuacio += 100 + (100 * 0.25 * files);
                    }
                    i++;
                }
                seguentBool = seguentFigura(mode);
                if (seguentBool == true) {
                    index_m_figures++;
                }
                if (index_m_figures > m_n_figures)
                {
                    m_acabar = true;
                }
                break;
            }
            index_m_moviments++;
            if (index_m_moviments > m_n_moviments)
            {
                index_m_moviments = 0;
            }
        }
        if (partidaAcabada(mode))
        {
            m_acabar = true;
        }
        */

    }
}