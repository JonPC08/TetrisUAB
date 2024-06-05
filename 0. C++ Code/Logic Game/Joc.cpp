#include "Joc.h"
#include <string>
#include <fstream>
#include <iostream>


using namespace std;


void Joc::inicialitza(const string& nomFitxer)
{
    int tipus, fila, columna, gir, color;
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		fitxer >> tipus >> fila >> columna >> gir;
		m_figura.inicialitza(TipusFigura(tipus), fila, columna);
		ColorFigura taulerInicial[MAX_FILA][MAX_COL];
		for (int i = 0; i < MAX_FILA; i++)
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer >> color;
				taulerInicial[i][j] = ColorFigura(color);
                m_tauler.setCasella(color, i, j);
			}
	}
    m_figura = Figura(ColorFigura(color), TipusFigura(tipus), fila - 1, columna - 1);
    Figura figuraVacia;
    giraFiguraInicial(GIR_HORARI, gir);
    actualitzarTauler(figuraVacia, m_figura);
    fitxer.close();
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
    Figura figuraAntes;
    figuraAntes.setPosicioFiguraX(m_figura.getPosicioFiguraX());
    figuraAntes.setPosicioFiguraY(m_figura.getPosicioFiguraY());
    int dimMatriu = m_figura.getDimMatriu();
    figuraAntes.setDimMatriu(dimMatriu);
    int matriuFigura[MAX_DIM][MAX_DIM];
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            matriuFigura[a][b] = m_figura.getMatriuFigura(a, b);
            figuraAntes.setMatriuFigura(a, b, m_figura.getMatriuFigura(a, b));
        }
    }
    int aux;
    // Transponer la matriz
    for (int a = 0; a < dimMatriu; a++) 
    {
        for (int b = a; b < dimMatriu; b++) 
        {
            aux = matriuFigura[a][b];
            matriuFigura[a][b] = matriuFigura[b][a];
            matriuFigura[b][a] = aux;
        }
    }
    // Invertir columnas para el giro horario o invertir filas para el giro antihorario
    if (direccio == GIR_HORARI) 
    {
        // Invertir columnas
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
    else // Gir anti-horari
    {
        // Invertir filas
        for (int a = 0; a < int(dimMatriu / 2); a++) 
        {
            for (int b = 0; b < dimMatriu; b++) 
            {
                aux = matriuFigura[a][b];
                matriuFigura[a][b] = matriuFigura[dimMatriu - a - 1][b];
                matriuFigura[dimMatriu - a - 1][b] = aux;
            }
        }
    }
    // Actualizamos valores
    int x = m_figura.getPosicioFiguraX();
    int y = m_figura.getPosicioFiguraY();
    bool colisiona = colisioFigura(matriuFigura, dimMatriu, x, y, x, y);
    if (colisiona == false) 
    {
        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                m_figura.setMatriuFigura(a, b, matriuFigura[a][b]);
            }
        }
    }
    actualitzarTauler(figuraAntes, m_figura);
    return !colisiona;
}


void Joc::giraFiguraInicial(DireccioGir direccio, int pos_inicial)
{
    Figura figuraAntes;
    figuraAntes.setPosicioFiguraX(m_figura.getPosicioFiguraX());
    figuraAntes.setPosicioFiguraY(m_figura.getPosicioFiguraY());
    int dimMatriu = m_figura.getDimMatriu();
    figuraAntes.setDimMatriu(dimMatriu);
    int matriuFigura[MAX_DIM][MAX_DIM];
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            matriuFigura[a][b] = m_figura.getMatriuFigura(a, b);
            figuraAntes.setMatriuFigura(a, b, m_figura.getMatriuFigura(a, b));
        }
    }
    for (int i = 0; i < pos_inicial; i++)
    {
        int aux;
        // Transponer la matriz
        for (int a = 0; a < dimMatriu; a++) 
        {
            for (int b = a; b < dimMatriu; b++) 
            {
                aux = matriuFigura[a][b];
                matriuFigura[a][b] = matriuFigura[b][a];
                matriuFigura[b][a] = aux;
            }
        }
        // Invertir columnas para el giro horario o invertir filas para el giro antihorario
        if (direccio == GIR_HORARI) 
        {
            // Invertir columnas
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
        else // Gir anti-horari
        {
            // Invertir filas
            for (int a = 0; a < int(dimMatriu / 2); a++) 
            {
                for (int b = 0; b < dimMatriu; b++) 
                {
                    aux = matriuFigura[a][b];
                    matriuFigura[a][b] = matriuFigura[dimMatriu - a - 1][b];
                    matriuFigura[dimMatriu - a - 1][b] = aux;
                }
            }
        }
    }
    // Actualizamos valores
    int x = m_figura.getPosicioFiguraX();
    int y = m_figura.getPosicioFiguraY();
    bool colisiona = colisioFigura(matriuFigura, dimMatriu, x, y, x, y);
    if (colisiona == false) 
    {
        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                m_figura.setMatriuFigura(a, b, matriuFigura[a][b]);
            }
        }
    }
    actualitzarTauler(figuraAntes, m_figura);
}


bool Joc::mouFigura(int dirX)
{
    Figura figuraAntes;
    figuraAntes.setPosicioFiguraX(m_figura.getPosicioFiguraX());
    figuraAntes.setPosicioFiguraY(m_figura.getPosicioFiguraY());
    int const dimMatriu = m_figura.getDimMatriu();
    figuraAntes.setDimMatriu(dimMatriu);
    int matriuFigura[MAX_DIM][MAX_DIM];
    bool movimentValid = true;
    // Caragamos la figura tal como era antes en figuraAntes
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            figuraAntes.setMatriuFigura(a, b, m_figura.getMatriuFigura(a, b));
        }
    }
    // Hacia la derecha (+1 en eje filas)
    if (dirX == 1)
    {
        // Comprovamos colision
        int y_anterior = m_figura.getPosicioFiguraY();
        m_figura.increasePosicioFiguraY();
        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                matriuFigura[a][b] =  m_figura.getMatriuFigura(a, b);
            }
        }
        int x = m_figura.getPosicioFiguraX();
        int y = m_figura.getPosicioFiguraY();
        bool colisiona = colisioFigura(matriuFigura, dimMatriu, x, y, x, y_anterior);
        // Si colisiona
        if (colisiona)
        {
            m_figura.decreasePosicioFiguraY();
            // Como colisiona devolvemos la figura a su posicion y devolvemos false en la funcion
            movimentValid = false;
        }
        else
        {
            // Añadir figura a matriz general
            movimentValid = true;
            actualitzarTauler(figuraAntes, m_figura);
        }
    }
    // Hacia la izquierda (-1 en eje filas)
    else if (dirX == -1)
    {
        // Comprovamos colision
        int y_anterior = m_figura.getPosicioFiguraY();
        m_figura.decreasePosicioFiguraY();
        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                matriuFigura[a][b] =  m_figura.getMatriuFigura(a, b);
            }
        }
        int x = m_figura.getPosicioFiguraX();
        int y = m_figura.getPosicioFiguraY();
        bool colisiona = colisioFigura(matriuFigura, dimMatriu, x, y, x, y_anterior);
        // Si colisiona
        if (colisiona)
        {
            m_figura.increasePosicioFiguraY();
            // Como colisiona devolvemos la figura a su posicion y devolvemos false en la funcion
            movimentValid = false;
        }
        else
        {
            // Añadir figura a matriz general
            movimentValid = true;
            actualitzarTauler(figuraAntes, m_figura);
        }
    }
    return movimentValid;
}


int Joc::baixaFigura()
{
    Figura figuraAntes;
    figuraAntes.setPosicioFiguraX(m_figura.getPosicioFiguraX());
    figuraAntes.setPosicioFiguraY(m_figura.getPosicioFiguraY());
    int dimMatriu = m_figura.getDimMatriu();
    figuraAntes.setDimMatriu(dimMatriu);
    int matriuFigura[MAX_DIM][MAX_DIM];
    int numeroFilasCompletas = 0;
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            figuraAntes.setMatriuFigura(a, b, m_figura.getMatriuFigura(a, b));
        }
    }
    int x_anterior = m_figura.getPosicioFiguraX();
    m_figura.increasePosicioFiguraX();
    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            matriuFigura[a][b] = m_figura.getMatriuFigura(a, b);
        }
    }
    int x = m_figura.getPosicioFiguraX();
    int y = m_figura.getPosicioFiguraY();
    bool colisiona = colisioFigura(matriuFigura, dimMatriu, x, y, x_anterior, y);
    if (colisiona)
    {
        m_figura.decreasePosicioFiguraX();
        // Recorrer matriz general mirando las 8 filas para ver cuales se han completado
        // Inicializacion a -1
        int listaFilasCompletas[MAX_FILA];
        for (int i = 0; i < MAX_FILA; i++) 
        {
            listaFilasCompletas[i] = -1;
        }
        bool continuar_linea;
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
        // En la lista filas completas estaran todas las filas que hay que eliminar
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

        // Bajar
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
    }
    else
    {   
        
        actualitzarTauler(figuraAntes, m_figura);
    }
    return numeroFilasCompletas;
}


void Joc::actualitzarTauler(Figura figuraAntes, Figura figuraAhora)
{
    // Elminiacion figura anterior
    int posicionFiguraAntesX = figuraAntes.getPosicioFiguraX();
    int posicionFiguraAntesY = figuraAntes.getPosicioFiguraY();
    for (int a = 0; a < figuraAntes.getDimMatriu(); a++)
    {
        for (int b = 0; b < figuraAntes.getDimMatriu(); b++)
        {
            if ((a + posicionFiguraAntesX >= 0) && (a + posicionFiguraAntesX <= (MAX_FILA - 1)) && (b + posicionFiguraAntesY >= 0) && (b + posicionFiguraAntesY <= MAX_COL)) 
            {
                if (figuraAntes.getMatriuFigura(a, b) != 0)
                {
                    m_tauler.setCasella(0, a + posicionFiguraAntesX, b + posicionFiguraAntesY);
                }
            }
        }
    }
    // Actualización figura ahora
    int posicionFiguraAhoraX = figuraAhora.getPosicioFiguraX();
    int posicionFiguraAhoraY = figuraAhora.getPosicioFiguraY();
    for (int a = 0; a < figuraAhora.getDimMatriu(); a++)
    {
        for (int b = 0; b < figuraAhora.getDimMatriu(); b++)
        {
            if ((a + posicionFiguraAhoraX >= 0) && (a + posicionFiguraAhoraX <= MAX_FILA - 1) && (b + posicionFiguraAhoraY >= 0) && (b + posicionFiguraAhoraY <= MAX_COL)) 
            {
                if (figuraAhora.getMatriuFigura(a, b) != 0)
                {
                    m_tauler.setCasella(figuraAhora.getTipusFigura(), a + posicionFiguraAhoraX, b + posicionFiguraAhoraY);
                }
            }
        }
    }
}


bool Joc::colisioFigura(int matriuFigura[MAX_DIM][MAX_DIM], int dim, int x, int y, int x_antes, int y_antes)
{
    bool colisiona = false;
    Tauler taulerNoFigura;
    // Copiamos Tablero
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            taulerNoFigura.setCasella(m_tauler.getCasella(i, j), i, j);
        }
    }
    // Ponemos 0 donde haya figura
    for (int a = 0; a < dim; a++)
    {
        for (int b = 0; b < dim; b++)
        {
            if (m_figura.getMatriuFigura(a, b) != 0) 
            {
                taulerNoFigura.setCasella(0, x_antes + a , y_antes + b);
            }
        }
    }
    int a = 0;
    int b = 0;
    while ((a < dim) && (colisiona == false))
    {
        b = 0;
        while ((b < dim) && (colisiona == false))
        {
            if (matriuFigura[a][b] != 0) 
            {       
                if (((y + b) < 0) || ((y + b) > MAX_COL - 1)) // Colision izquierda derecha
                {
                    colisiona = true;
                }
                else if ((x + a) > MAX_FILA - 1) // Colision abajo
                {
                    colisiona = true;
                }
                else
                {
                    if (taulerNoFigura.getCasella(x + a, y + b) != 0)
                    {
                        colisiona = true;
                    }
                    else
                    {
                        colisiona = false;
                    }
                }
            }
            b++;
        }
        a++;
    }
    return colisiona;
}