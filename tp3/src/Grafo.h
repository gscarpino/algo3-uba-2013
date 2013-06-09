#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <algorithm>



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
        void agregarArista(unsigned int n1, unsigned int n2);
        unsigned int cantAristas() const;

    private:
        unsigned int nodos;
        vector< vector <unsigned int> > aristas;


};

#endif // GRAFO_H
