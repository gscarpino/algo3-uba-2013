#ifndef SOL_H
#define SOL_H

#include "Redefs.h"


class Sol{
    private:
        int id;
        int rotaciones;
        Posicion posicion;

    public:

    Sol();
    Sol(int id, int rotaciones, Posicion posicion);
    void imprimir() const;
};

#endif // SOL_H
