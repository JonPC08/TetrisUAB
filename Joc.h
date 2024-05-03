#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

const int MAX_FIGURES = 4;

//CAMBIAR Poner:const int DADES_INSTRUCCIO = 4;

class Joc
{
public:
	Joc() {}
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void actualitzarTauler(Figura figuraAntes, Figura figuraAhora);
	void escriuTauler(const string& nomFitxer);
	bool colisioFigura(int matriuFigura[MAX_DIM][MAX_DIM], int dim, int x, int y);

private:
	Tauler m_tauler;
	Figura m_figura;
	//CAMBIAR: int m_dadesInstruccio[DADES_INSTRUCCIO];
	int m_seguentsFigures[MAX_FIGURES];
};

#endif