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
        vector< Camino > getAristas();
//        void agregarArista(unsigned int n1, unsigned int n2, pair<bool,unsigned int> a);
        void agregarArista(const Camino &c);
        unsigned int cantAristas() const;
        Grafo AGM();
        bool cmpCamino(Camino &a, Camino &b);

    private:
        unsigned int nodos;
        vector< Camino > aristas;


};

#endif // GRAFO_H
