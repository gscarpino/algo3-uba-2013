#include "Grafo.h"

Grafo::Grafo(unsigned int cantNodos){
    this->nodos = cantNodos;
    this->ejes = 0;
    vector<unsigned int> temp;
    temp.reserve(cantNodos);

    for(unsigned int i = 0; i < cantNodos; i++){
        this->aristas.push_back(temp);
    }

}

Grafo::Grafo(const Grafo& other){
    this->nodos = other.nodos;
    this->aristas = other.aristas;
    this->ejes = other.ejes;
}


unsigned int Grafo::cantNodos() const{
    return this->nodos;
}


void Grafo::agregarArista(unsigned int n1, unsigned int n2){
    this->aristas[n1].push_back(n2);
    this->aristas[n2].push_back(n1);
    this->ejes++;
}

unsigned int Grafo::cantAristas() const{
    return this->ejes;
}


vector<unsigned int> Grafo::vecinosDe(const unsigned int nodo) const{
    return this->aristas[nodo];
}

unsigned int Grafo::gradoMaximo() const{
    unsigned int res = 0;

    for(unsigned int i = 0; i < this->aristas.size(); i++){
        if(res < this->aristas[i].size()){
            res = this->aristas[i].size();
        }
    }

    return res;
}


unsigned int Grafo::impacto(const vector<int> &coloreo) const{
    unsigned int res = 0;
    for(unsigned int i = 0; i < this->nodos; i++){
        for(unsigned int j = 0; j < this->aristas[i].size(); j++){
            if(coloreo[i] != -1){
                if(coloreo[i] == coloreo[this->aristas[i][j]]){
                    res++;
                }
            }
        }
    }
    res /=2;
    return res;
}


bool Grafo::colorLegalDeNodo(const unsigned int nodo, const vector<int> &coloreo, const int color) const{
    bool res = true;

    for(unsigned int i = 0; i < this->aristas[nodo].size(); i++){
        if(coloreo[this->aristas[nodo][i]] == color){
            res = false;
            break;
        }
    }

    return res;
}


bool Grafo::coloreoLegal(const vector<int> &coloreo) const{
    bool res = true;
    for(unsigned int i = 0; i < this->nodos; i++){
        res = this->colorLegalDeNodo(i,coloreo,coloreo[i]);
        if(!res){
            break;
        }
    }
    return res;
}


bool Grafo::sonVecinos(unsigned int n1, unsigned int n2) const{
    bool res = false;
    for(unsigned int e = 0; e < this->aristas[n1].size(); e++){
        if(aristas[n1][e] == n2){
            res = true;
            break;
        }
    }
    return res;
}
