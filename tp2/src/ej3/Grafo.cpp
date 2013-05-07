#include "Grafo.h"



Grafo::Grafo(unsigned int cantNodos){
    this->nodos = cantNodos;
    //evitamos realocacion de memoria
    this->aristas.reserve(cantNodos);
    vector<unsigned int> fila(cantNodos,0);
    for(unsigned int i = 0; i < cantNodos; i++){
        this->aristas.push_back(fila);
    }
    cantidadAristas = 0;
}

Grafo::Grafo(const Grafo& other)
{
    this->nodos = other.nodos;
    this->aristas = other.aristas;
    this->cantidadAristas = other.cantidadAristas;
}


unsigned int Grafo::getNodos(){
    return this->nodos;
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
    this->aristas[c.first][c.second] = 1;
    this->cantidadAristas++;
}

unsigned int Grafo::cantAristas() const{
    return this->cantidadAristas;
}

vector<unsigned int> Grafo::vecinosDe(unsigned int nodo){
    vector<unsigned int> res;
    for(unsigned int i = 0; i < this->nodos; i++){
        if(nodo != i){
            if(aristas[nodo][i] == 1){
                res.push_back(i);
            }
        }
    }
    return res;
}


vector<unsigned int> Grafo::grupoDeRiesgo(){
    vector<unsigned int> res;
    for(unsigned int i = 0; i < nodos; i++){
        vector<unsigned int> nodosMarcados(nodos,0);
        marcarNodos(i,nodosMarcados);
        if(todosMarcados(nodosMarcados)){
            res.push_back(i);
        }
    }

    return res;
}

bool Grafo::todosMarcados(const vector<unsigned int> &v){
    bool res = true;
    for(unsigned int i = 0; i < v.size(); i++){
        if(v[i] == 0){
            res = false;
            break;
        }
    }
    return res;
}

void Grafo::marcarNodos(unsigned int nodo, vector<unsigned int> &nodosMarcados){
    nodosMarcados[nodo] = 1;
    vector<unsigned int> vecinos(this->vecinosDe(nodo));

    for(unsigned int i = 0; i < vecinos.size(); i++){
        if(nodosMarcados[vecinos[i]] == 0){
            marcarNodos(vecinos[i],nodosMarcados);
        }
    }
}
