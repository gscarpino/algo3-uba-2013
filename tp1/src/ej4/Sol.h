#ifndef SOL_H
#define SOL_H

#include <iostream>
using namespace std;
typedef pair<unsigned int, unsigned int> Posicion;



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
