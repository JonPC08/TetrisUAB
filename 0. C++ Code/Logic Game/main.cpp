//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)


#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 
#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop


#endif


#include "./Partida.h"
#include "./InfoJoc.h"
#include "./Tetris.h"


// CAMBIAR EL PATH
string scoreboard = "C:/Users/marcd/Desktop/Tetris Parte 2/intro_llibreria_grafica_estudiants/0. C++ Code/Logic Game/scoreboard.txt";
string partida = "C:/Users/marcd/Desktop/Tetris Parte 2/intro_llibreria_grafica_estudiants/1. Resources/data/Games/partida.txt";
string figures = "C:/Users/marcd/Desktop/Tetris Parte 2/intro_llibreria_grafica_estudiants/1. Resources/data/Games/figures.txt";
string moviments = "C:/Users/marcd/Desktop/Tetris Parte 2/intro_llibreria_grafica_estudiants/1. Resources/data/Games/moviments.txt";


int main(int argc, const char* argv[])
{
    int mode = 0;
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    //Mostrem la finestra grafica
    pantalla.show();
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    Tetris tetris;
    while (mode != 3) // Salirse // Por algun motivo si juegas una vez ya no puedes jugar porque la interfaz grafica crashea el juego (enteoria esta bien y se libera la memoria con SDL_Quit())
    {
        mode = tetris.mostraMenu() - 1;
        if ((mode == 0) || (mode == 1)) //  0 y 1
        {
            Partida game;
            // game.inicialitza(mode, "./data/Games/partida.txt", "./data/Games/figures.txt", "./data/Games/moviments.txt"); // NO VA ASI QUE HAY QUE CAMBIAR EL PATH A MANO
            game.inicialitza(mode, partida, figures, moviments); // CAMBIAR
            do
            {
                LAST = NOW;
                NOW = SDL_GetPerformanceCounter();
                deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
                // Captura tots els events de ratolí i teclat de l'ultim cicle
                pantalla.processEvents();
                game.actualitza(mode, deltaTime);
                // Actualitza la pantalla
                pantalla.update();
            } while ((!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) && (!game.getm_acabar()));
            if (mode == 0)
            { 
                // Sortim del bucle si pressionem ESC
                string filename = scoreboard;
                string nom;
                cout << endl << "Introdueix el teu nom: ";
                cin >> nom;
                cout << endl;
                tetris.guardaPuntuacio(filename, game.getPuntuacio(), nom);
            }
            else 
            {
                cout << endl;
            }
            //Instruccio necesaria per alliberar els recursos de la llibreria 
            SDL_Quit();
        }
        else if (mode == 2) // 2
        {
            string filename = scoreboard;
            int num_elements = -1;
            string punts;
            string name;
            ifstream fitxer;
            fitxer.open(filename);
            cout << endl;
            if (fitxer.is_open())
            {
                fitxer >> num_elements;
                for (int i = 0; i < num_elements; i++)
                {
                    fitxer >> punts >> name;
                    cout << punts << " " << name << endl;
                }
                fitxer.close();
                cout << endl;
            }
        }
        else // 3
        {
            // Salimos
        }
    }


    return 0;
}