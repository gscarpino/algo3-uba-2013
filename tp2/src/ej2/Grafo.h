#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
using namespace std;

typedef vector< pair<bool, unsigned int> > Vec;
typedef vector<Vec> Matriz;
typedef pair<pair<unsigned int, unsigned int>, pair<bool, unsigned int> > Camino;

class Grafo
{
    public:
        Grafo();
        Grafo(unsigned int cantNodos);
        Grafo(const Grafo& other);
        Grafo& operator=(const Grafo& other);
        unsigned int getNodos();
        unsigned int getAristas();
        void agregarArista(unsigned int n1, unsigned int n2, pair<bool,unsigned int> a);
        Grafo AGM() const;

    private:
        unsigned int nodos;
        unsigned int aristas;
        Matriz ma;

};

#endif // GRAFO_H
