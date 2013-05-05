#include "Grafo.h"



Grafo::Grafo()
{
    this->nodos = 0;
    this->aristas = 0;
}


Grafo::Grafo(unsigned int cantNodos){
    this->nodos = cantNodos;
    this->aristas = 0;
    Vec fila(cantNodos,make_pair(false,0));
    for(unsigned int i = 0; i < cantNodos; i++){
        this->ma.push_back(fila);
    }
}

Grafo::Grafo(const Grafo& other)
{
    this->nodos = other.nodos;
    this->aristas = other.aristas;
    this->ma = other.ma;
}

Grafo& Grafo::operator=(const Grafo& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


unsigned int Grafo::getNodos(){
    return this->nodos;
}

unsigned int Grafo::getAristas(){
    return this->aristas;
}

void Grafo::agregarArista(unsigned int n1, unsigned int n2, pair<bool,unsigned int> a){
    if(n1 > this->nodos || n2 > this->nodos){
        cerr << "Error: algun nodo no existente en el grafo" << endl;
    }
    else{
        this->ma[n1][n2] = a;
    }
}

Grafo Grafo::AGM() const{
    DisjointSet ds(this->nodos);
    vector<Camino> ruta;
    //ordenar aristas grafo
    //e == 1 entonces de mayor a menor, e==0 entonces de menor a mayor
    //generar agm
}
