#ifndef PIEZA_H
#define PIEZA_H

#include "Redefs.h"


class Pieza
{
    public:
        Pieza(const Matriz &p, const unsigned int id);
        Pieza(const Pieza &otra);
        unsigned int getRows() const;
        unsigned int getCols() const;
        unsigned int getID() const;
        void imprimir() const;
        unsigned int getColor(const unsigned int x, const unsigned int y) const;
        unsigned int getColor(const Posicion &p) const;
        Pieza rotar() const;
        friend bool operator<(const Pieza &p1, const Pieza &p2);
        friend bool operator!=(const Pieza &p1, const Pieza &p2);
        Pieza& operator=(const Pieza &otro);

    private:
        Matriz m;
        unsigned int rows;
        unsigned int cols;
        unsigned int id;
};

#endif // PIEZA_H
