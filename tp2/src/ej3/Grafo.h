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
        void agregarArista(const pair< unsigned int, unsigned int > &c);
        unsigned int cantAristas() const;
        vector<unsigned int> vecinosDe(unsigned int nodo);
        vector<unsigned int> grupoDeRiesgo();

    private:
        unsigned int nodos;
//        vector< pair< unsigned int, unsigned int > > aristas;
        unsigned int cantidadAristas;
        vector< vector< unsigned int > > aristas;

        void marcarNodos(unsigned int nodo, vector<unsigned int> &nodosMarcados);
        bool todosMarcados(const vector<unsigned int> &v);

};

#endif // GRAFO_H
