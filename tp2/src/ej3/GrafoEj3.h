#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>

using namespace std;

class Grafo{

    public:
        Grafo(unsigned int cant);
        Grafo(const Grafo& other);
        void agregarArista(const unsigned int u, const unsigned int v); //agrega la arista dirigida
        unsigned int cantidadNodos();
        unsigned int cantidadAristas();
        vector<unsigned int> hijos(unsigned int nodo);

        vector< vector<unsigned int> > grupoDeRiesgoMaximales();

	private:
        unsigned int cantNodos;
        unsigned int cantAristas;
        vector< vector<unsigned int> > aristas;
        vector<unsigned int> indice;
        vector<unsigned int> bajoIndice;
        vector<bool> presente;

        //Aux
        void tarjanAlgorithm(unsigned int &index, stack<unsigned int> &pila, unsigned int nodo, vector<vector<unsigned int> > &componentes);
//        bool pertenecePila(stack<unsigned int> pila, unsigned int nodo);


};

#endif // GRAFO_H
