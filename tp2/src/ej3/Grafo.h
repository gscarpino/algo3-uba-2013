#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "Redefs.h"


using namespace std;

class Grafo
{
    public:

        Grafo(unsigned int cantNodos);
        Grafo(const Grafo& other);
        unsigned int getNodos();
        vector< pair< unsigned int, unsigned int > > getAristas();
        void agregarArista(const pair< unsigned int, unsigned int > &c);
        unsigned int cantAristas() const;

    private:
        unsigned int nodos;
        vector< pair< unsigned int, unsigned int > > aristas;


};

#endif // GRAFO_H
