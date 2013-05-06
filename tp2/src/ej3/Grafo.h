#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "Redefs.h"


using namespace std;
//
//typedef vector< pair<bool, unsigned int> > Vec;
//typedef vector<Vec> Matriz;
//typedef pair<pair<unsigned int, unsigned int>, pair<bool, unsigned int> > Camino;

class Grafo
{
    public:

        Grafo(unsigned int cantNodos);
        Grafo(const Grafo& other);
        unsigned int getNodos();
        vector< vector< bool > > getAristas();
        void agregarArista(const unsigned int a, const unsigned int b);
        unsigned int cantAristas() const;
        Grafo AGM();

    private:
        unsigned int nodos;
        unsigned int cantArist;
        vector< vector< bool > > aristas;


};

#endif // GRAFO_H
