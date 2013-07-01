#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <algorithm>



using namespace std;

class Grafo
{
    public:

        Grafo(unsigned int cantNodos);
        Grafo(const Grafo& other);
        unsigned int cantNodos() const;
        unsigned int cantAristas() const;
        void agregarArista(unsigned int n1, unsigned int n2);
        vector<unsigned int> vecinosDe(const unsigned int nodo) const;
        unsigned int gradoDe(const unsigned int nodo) const;
        bool sonVecinos(unsigned int n1, unsigned int n2) const;
        unsigned int gradoMaximo() const;
        unsigned int impacto(const vector<unsigned int> &coloreo) const;
        bool colorLegalDeNodo(const unsigned int nodo, const vector<unsigned int> &coloreo, unsigned int color ) const;
        bool coloreoLegal(const vector<unsigned int> &coloreo) const;
        void ordenarAristas(unsigned int orden);
        void imprimir();

    private:
        unsigned int nodos;
        unsigned int ejes;
        vector< vector <unsigned int> > aristas;



};

#endif // GRAFO_H
