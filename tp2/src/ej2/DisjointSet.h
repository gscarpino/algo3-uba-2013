#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <iostream>
#include <map>

using namespace std;

class DisjointSet
{
    public:
        DisjointSet(unsigned int cant);
        void unir(unsigned int x, unsigned int y);
        bool buscar(unsigned int x, unsigned int y);
        unsigned int tamanio() const;
        void imprimir();

    private:
        map<int,int> clases;
};

#endif // DISJOINTSET_H
