#ifndef FIGURA_H
#define FIGURA_H


const int MAX_DIM = 4;


typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;


typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S,
} TipusFigura;


typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;


class Figura
{
    public:
        // Constructors
        Figura(); // Coinstructor per defecte
        Figura(const ColorFigura colorFigura, const TipusFigura tipusFigura, const int x, const int y); // Coinstructor per parametres
        // Setters
        void setPosicioFiguraX(const int x);
        void setPosicioFiguraY(const int y);
        void setMatriuFigura(const int a, const int b, const int valor);
        void setDimMatriu(const int dim);
        void setTipusFigura(const int tipus);
        // Getters
        int getPosicioFiguraX() const {return m_posicioFigura[0];};
        int getPosicioFiguraY() const {return m_posicioFigura[1];};
        int getMatriuFigura(const int a, const int b) const {return m_matriuFigura[a][b];};
        int getDimMatriu() const {return m_dimMatriu;};
        int getTipusFigura() const {return m_tipusFigura;};
        // Metodes
        void inicialitza(TipusFigura tipusFigura, int fila, int columna);
        void inicialitzaForma(TipusFigura tipusFigura);
        void decreasePosicioFiguraX();
        void increasePosicioFiguraX();
        void decreasePosicioFiguraY();
        void increasePosicioFiguraY();
        void dibuixa(int x, int y); // Dibuixa la figura al lloc correspoent depenent dels parametres
    private:
        ColorFigura m_colorFigura;
        TipusFigura m_tipusFigura;
        int m_matriuFigura[MAX_DIM][MAX_DIM];
        int m_dimMatriu;
        // Index 0 = fila, Index 1 = columna
        int m_posicioFigura[2];
};


#endif
