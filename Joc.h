#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

const int MAX_FIGURES = 200;

class Joc
{
public:
	Joc() {}
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);

private:
	Tauler m_tauler;
	Figura m_figura[MAX_FIGURES];
	int n_m_figura;
	int m_seguentsFigures[MAX_FIGURES];
};

int arraySize(int array[MAX_FIGURES]);

#endif