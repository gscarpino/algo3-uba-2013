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

        vector< vector<unsigned int> > grupoDeRiesgoMaximalesNoLineal();
        vector< vector<unsigned int> > grupoDeRiesgoMaximalesLineal();

	private:
        unsigned int cantNodos;
        unsigned int cantAristas;
        vector< vector<unsigned int> > aristas;
        vector<unsigned int> indice;
        vector<unsigned int> bajoIndice;

        //No Lineal
        bool pertenece(const unsigned int n, const vector<unsigned int> &v) const;
        bool contagia(const unsigned int n, const vector<unsigned int> &v) const;
        bool loContagian(const unsigned int n, const vector<unsigned int> &v) const;
        void borrarDuplicadosYnoMaximales(vector< vector<unsigned int> > &grupos);
        unsigned int relacion(const vector<unsigned int> &v1,const vector<unsigned int> &v2);

        //Linea
        void tarjanAlgorithm(unsigned int &index, stack<unsigned int> &pila, unsigned int nodo, vector<vector<unsigned int> > &componentes);
        bool pertenecePila(stack<unsigned int> pila, unsigned int nodo);


};

#endif // GRAFO_H
