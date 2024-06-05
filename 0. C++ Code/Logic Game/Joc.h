#ifndef Joc_H
#define Joc_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;


const int MAX_FIGURES = 4;


class Joc
{
public:
		Joc() {;}; // Constructor
		void inicialitza(const string& nomFitxer);
		bool giraFigura(DireccioGir direccio);
		bool mouFigura(int dirX);
		int baixaFigura();
		void actualitzarTauler(Figura figuraAntes, Figura figuraAhora);
		void escriuTauler(const string& nomFitxer);
		bool colisioFigura(int matriuFigura[MAX_DIM][MAX_DIM], int dim, int x, int y, int x_antes, int y_antes);
		void giraFiguraInicial(DireccioGir direccio, int pos_inicial);
		// inlane
		// getter
		Figura& getFigura() { return m_figura; }; // Nueva funcion para poder devolver figura
		Tauler& getTauler() { return m_tauler; }; // Nueva funcion para poder devolver tauler
		//setter
		void setFigura(const Figura& figura) { m_figura = figura; }; // Nueva funcion para poder meter la figura
	private:
		Tauler m_tauler;
		Figura m_figura;
};

#endif