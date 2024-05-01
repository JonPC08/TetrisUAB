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

bool Joc::mouFigura(int dirX)
{
    Figura figuraAntes;
    figuraAntes.setPosicioFiguraX(m_figura.getPosicioFiguraX());
    figuraAntes.setPosicioFiguraY(m_figura.getPosicioFiguraY());
    int dimMatriu = m_figura[n_m_figura].getDimMatriu();
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

        /* J: Estoy seguro de que esto aqui es necesario, ya que sino la matriz que estamos pasando no es la de
        la nueva posicion, sino la que hemos cargado antes de mover. Comprovar si esto es cierto y ajustar en los
        demas sitios si es necesario.
        */
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
            Figura figuraAhora;

            for (int a = 0; a < dimMatriu; a++)
            {
                for (int b = 0; b < dimMatriu; b++)
                {
                    figuraAhora.setMatriuFigura(a, b, m_figura[n_m_figura].getMatriuFigura(a, b));
                }
            }
            /* J: Aqui no ha chocado, por tanto si pasamos figuraAntes para que elmine la anterior y ponga la nueva
            */
            movimentValid = true;
            actualitzarTauler(figuraAntes, figuraAhora);
        }
    }
    // Hacia la izquierda (-1 en eje Y)
    else if (dirX == -1)
    {
        // Comprovamos colision
        m_figura[n_m_figura].decreasePosicioFiguraY();

        /* J: Estoy seguro de que esto aqui es necesario, ya que sino la matriz que estamos pasando no es la de
        la nueva posicion, sino la que hemos cargado antes de mover. Comprovar si esto es cierto y ajustar en los
        demas sitios si es necesario.
        */
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
            Figura figuraAhora;

            for (int a = 0; a < dimMatriu; a++)
            {
                for (int b = 0; b < dimMatriu; b++)
                {
                    figuraAhora.setMatriuFigura(a, b, m_figura[n_m_figura].getMatriuFigura(a, b));
                }
            }
            /* J: Aqui no ha chocado, por tanto si pasamos figuraAntes para que elmine la anterior y ponga la nueva
            */
            movimentValid = true;
            actualitzarTauler(figuraAntes, figuraAhora);
        }
    }
    return movimentValid;
}

int Joc::baixaFigura()
{
    Figura figuraAntes;
    figuraAntes.setPosicioFiguraX(m_figura.getPosicioFiguraX());
    figuraAntes.setPosicioFiguraY(m_figura.getPosicioFiguraY());
    int dimMatriu = m_figura[n_m_figura].getDimMatriu();
    int matriuFigura[dimMatriu][dimMatriu];
    int liniesCompletades = 0;

    for (int a = 0; a < dimMatriu; a++)
    {
        for (int b = 0; b < dimMatriu; b++)
        {
            matriuFigura[a][b] =  m_figura[n_m_figura].getMatriuFigura(a, b);
            figuraAntes.setMatriuFigura(a, b, m_figura[n_m_figura].getMatriuFigura(a, b));
        }
    }

    m_figura[n_m_figura].increasePosicioFiguraX();
    bool colisiona = colisioFigura(matriuFigura, dimMatriu);

    if (colisiona)
    {
        m_figura[n_m_figura].decreasePosicioFiguraX();

        // M: Recorrer matriz general mirando las 8 filas para ver cuales se han completado
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
            /* M: Una vez sepamos cuantas se han completado asignamos guardamos las lineas completadas en un 
            array para saber cuales se han completado y igualamos lineascompletadas = a esse numero*/
            if (continuar_linea) {
                listaFilasCompletas[numeroFilasCompletas] = a;
                numeroFilasCompletas++;
            }
        }
        
        // M: En la lista filas completas estaran todas las filas que hay que eliminar
        for (int a = 0; a < numeroFilasCompletas; a++) 
        {
            for (int b = 0; b < 8; b++) 
            {
                // J: Tal vez es (0, b, listaFilasCompletas[a])
                m_tauler.setCasella(0, listaFilasCompletas[a], b);
            }
        }

        // M: Añadir figura a matriz general
        Figura figuraAhora;
        Figura figuraVacia;

        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                figuraAhora.setMatriuFigura(a, b, m_figura[n_m_figura].getMatriuFigura(a, b));
                figuraVacia.setMatriuFigura(a, b, 0);
            }
        }
        /* J: Al pasar figuraVacia que es todo 0, no elimina nada y simplemente imprime donde esta en ese momento
              se podria llegar a omitir, ya que tecnicamente ya estaba impresa.
        */
        actualitzarTauler(figuraVacia, figuraAhora);


        /*  M: Ahora gracias al array anteriormente creado localizamos dicha posicion de la fila y bajamos toas 
              las superiores una posicion hasta que el array se acabe (podemos inicializar el array array[8] como -1 para saber cuando se han acabado)
            J: Hay que chequear que si al bajar las casillas suspendidas en el aire completamos otra fila.
        */


        // M: Hacer n_m_figura++
        n_m_figura++;
    }
    else
    {
        // M: Añadir figura a matriz general
        Figura figuraAhora;
        Figura figuraVacia;

        for (int a = 0; a < dimMatriu; a++)
        {
            for (int b = 0; b < dimMatriu; b++)
            {
                figuraAhora.setMatriuFigura(a, b, m_figura[n_m_figura].getMatriuFigura(a, b));
            }
        }
        /* J: Aqui no ha chocado, por tanto si pasamos figura vacia para que elmine la anterior y ponga la nueva
        */
        actualitzarTauler(figuraAntes, figuraAhora);

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