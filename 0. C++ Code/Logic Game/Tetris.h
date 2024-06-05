#ifndef TETRIS_H
#define TETRIS_H
#include "Partida.h"
#include <fstream>
#include <list>


const int MAX_ELEMENTOS = 200;


class Tetris
{
	public:
		Partida inicialitzaJoc(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
		Partida getPartida() const { return m_partida; }; // inline
		void guardaPuntuacio(const string& nomFitxer, int punts, const string& nom);
		int mostraMenu();
	private:
		Partida m_partida;
};


#endif