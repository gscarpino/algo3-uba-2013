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

Grafo& Grafo::operator=(const Grafo& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


unsigned int Grafo::getNodos(){
    return this->nodos;
}

vector< Camino > Grafo::getAristas(){
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

void Grafo::agregarArista(const Camino &c){
    this->aristas.push_back(c);
}

unsigned int Grafo::cantAristas() const{
    return this->aristas.size();
}

bool Grafo::cmpCamino(Camino &a, Camino &b){
    if(a.second.first == b.second.first){
        if(a.second.first){
            return a.second.second < b.second.second;
        }
        else{
            return a.second.second > b.second.second;
        }
    }
    else{
        return a.second.first;
    }
}

Grafo Grafo::AGM(){
    Grafo res(nodos);
//    DisjointSet ds(this->nodos);
//    for(unsigned int i = 0; i < this->aristas.size(); i++){
//        cout << "(" << this->aristas[i].first.first << "," << this->aristas[i].first.second << "," << this->aristas[i].second.first << "," << this->aristas[i].second.second << ") ";
//    }
//    cout << endl;

    sort(this->aristas.begin(),this->aristas.end(),cmpCamino);

//    for(unsigned int i = 0; i < this->aristas.size(); i++){
//        cout << "(" << this->aristas[i].first.first << "," << this->aristas[i].first.second << "," << this->aristas[i].second.first << "," << this->aristas[i].second.second << ") ";
//    }
//    cout << endl;
    //ordenar aristas grafo
    //e == 1 entonces de mayor a menor, e==0 entonces de menor a mayor
    //generar agm

    return res;
}



