#ifndef SOL_H
#define SOL_H

#include <iostream>
#include <cstring>
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

friend ostream& operator<<(ostream& out, const Sol &s);

};

#endif // SOL_H
