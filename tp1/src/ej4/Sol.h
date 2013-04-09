#include <iostream>

using namespace std;

typedef pair<int,int> Posicion;


#ifndef SOL_H
#define SOL_H

class Sol{
    private:
        int id;
        int rotaciones;
        Posicion posicion;

    public:

    Sol();
    Sol(int id, int rotaciones, Posicion posicion);
};

#endif // SOL_H
