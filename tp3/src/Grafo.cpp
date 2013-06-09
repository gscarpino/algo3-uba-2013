#include "Grafo.h"



Grafo::Grafo(unsigned int cantNodos){
    this->nodos = cantNodos;
    //evitamos realocacion de memoria
    this->aristas.reserve(cantNodos*cantNodos);
}

Grafo::Grafo(const Grafo& other)
{
    this->nodos = other.nodos;
    this->aristas = other.aristas;
}


unsigned int Grafo::getNodos(){
    return this->nodos;
}


void Grafo::agregarArista(unsigned int n1, unsigned int n2){

}

unsigned int Grafo::cantAristas() const{
    return this->aristas.size();
}
