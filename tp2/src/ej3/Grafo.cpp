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

vector< pair< unsigned int, unsigned int > > Grafo::getAristas(){
    return this->aristas;
}

//void Grafo::agregarArista(unsigned int n1, unsigned int n2, pair<bool,unsigned int> a){
//    if(n1 > this->nodos || n2 > this->nodos){
//        cerr << "Error: algun nodo no existente en el grafo" << endl;
//    }
//    else{
//        this->aristas.push_back(a);
//    }
//}

void Grafo::agregarArista(const pair< unsigned int, unsigned int > &c){
    this->aristas.push_back(c);
}

unsigned int Grafo::cantAristas() const{
    return this->aristas.size();
}


