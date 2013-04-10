#ifndef TABLERO_H
#define TABLERO_H


#include "Redefs.h"
#include "Pieza.h"




class Tablero
{
    public:
        Tablero(unsigned int rows, unsigned int cols);
        Tablero(const Matriz &matriz, unsigned int rows, unsigned int cols);
        Tablero(const Tablero &otro);
        void imprimir() const;
        void imprimirConFichas() const;
        vector<Posicion> posiblesPosiciones(const Pieza &pieza) const;
        void ubicarFicha(const Pieza &pieza, const unsigned int rotacion, const Posicion &pos);
        bool encaja(const Pieza &pieza, const Posicion &pos) const;
        unsigned int getRows() const;
        unsigned int getCols() const;
        bool ocupado(const Posicion &pos) const;
        bool completo() const;
        bool cubreTodo(const vector<Pieza> &piezas) const;
        Tablero& operator=(const Tablero &otro);
        Solucion obtenerPiezas();

    private:
        vector<vector<pair< unsigned int, bool> > > m;
        unsigned int rows;
        unsigned int cols;
        Solucion piezasColocadas;
};

#endif // TABLERO_H
