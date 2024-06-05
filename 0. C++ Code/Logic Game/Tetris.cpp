#include "tetris.h"
#include "GraphicManager.h"
#include <iostream>


int Tetris::mostraMenu()
{
	int opcio = 0;
	do {
		cout << "MENU PRINCIPAL" << endl;
		cout << "==============" << endl;
		cout << "1. JUGAR MODE NORMAL" << endl;
		cout << "2. JUGAR MODE TEST" << endl;
		cout << "3. MOSTRAR PUNTUACIONS" << endl;
		cout << "4. SORTIR" << endl;
		cout << "Introdueix el numero corresponent a la opcio que vulguis: ";
		cin >> opcio;
	} while ((opcio != 4) && (opcio != 3) && (opcio != 2) && (opcio != 1));
	return opcio;
}


Partida Tetris::inicialitzaJoc(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
	Partida game;
	if (mode == 0) 
	{
		game.creaFigura(COLOR_MAGENTA, FIGURA_O, 0, 1);
	}
	else if (mode == 1)
	{
		game.inicialitza(mode, fitxerInicial, fitxerFigures, fitxerMoviments);
	}
	return game;
}


void Tetris::guardaPuntuacio(const string& nomFitxer, int punts, const string& nom)
{
	// Abrimos archivo y ordenamos puntuaciones
	ifstream fitxer;
	fitxer.open(nomFitxer);
	int num_elements = -1;
	int puntuacions[MAX_ELEMENTOS];
	string noms[MAX_ELEMENTOS];
	if (fitxer.is_open())
	{
		fitxer >> num_elements;
		for (int i = 0; i < MAX_ELEMENTOS; i++)
		{
			puntuacions[i] = -1;
			noms[i] = "";
		}
		for (int i = 0; i < num_elements; i++)
		{
			fitxer >> puntuacions[i] >> noms[i];
		}
		fitxer.close();
	}
	puntuacions[num_elements] = punts;
	noms[num_elements] = nom;
	num_elements++;
	// Ordenamos con Bubblesort
	for (int i = 0; i < num_elements - 1; ++i) {
		for (int j = 0; j < num_elements - i - 1; ++j) {
			if (puntuacions[j] < puntuacions[j + 1]) {
				int temp_int = puntuacions[j];
				string temp_string = noms[j];
				puntuacions[j] = puntuacions[j + 1];
				noms[j] = noms[j + 1];
				puntuacions[j + 1] = temp_int;
				noms[j + 1] = temp_string;
			}
		}
	}
	// Convertimos a string
	string puntuacions_string[MAX_ELEMENTOS];
	for (int i = 0; i < MAX_ELEMENTOS; i++)
	{
		puntuacions_string[i] = "-1";
	}
	for (int i = 0; i < num_elements; i++) 
	{
		puntuacions_string[i] = to_string(puntuacions[i]);
	}
	// Output a fitxer
	ofstream fitxer2;
	fitxer2.open(nomFitxer);
	if (fitxer2.is_open())
	{
		fitxer2 << to_string(num_elements);
		fitxer2 << endl;
		for (int i = 0; i < num_elements; i++)
		{
			fitxer2 << puntuacions_string[i] << " " << noms[i];
			fitxer2 << endl;
		}
		fitxer2.close();
	}
}


void escriuPuntuacio(const string& nomFitxer, string array[MAX_ELEMENTOS], int num_elements)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		fitxer << to_string(num_elements);
		fitxer << endl;
		for (int i = 0; i < num_elements; i++)
		{
			fitxer << array[i];
			fitxer << endl;
		}
		fitxer.close();
	}
}