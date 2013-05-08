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


vector< vector<unsigned int> > Grafo::grupoDeRiesgoMaximales(){
    vector< vector<unsigned int> > res;

    for(unsigned int i = 0; i < nodos; i++){
        vector<unsigned int> unitario(1,i);
        res.push_back(unitario);
    }

    for(unsigned int i = 0; i < nodos; i++){
        for(unsigned int j = 0; j < res.size(); j++){
            if(!pertenece(i,res[j])){
                if(contagia(i,res[j]) && loContagian(i,res[j])){
                    res[j].push_back(i);
                }
            }
        }
    }

    borrarDuplicadosYnoMaximales(res);

    return res;
}

bool Grafo::pertenece(const unsigned int n, const vector<unsigned int> &v) const{
    bool res = false;
    for(unsigned int i = 0; i < v.size(); i++){
        if(n == v[i]){
            res = true;
            break;
        }
    }
    return res;
}


bool Grafo::contagia(const unsigned int n, const vector<unsigned int> &v) const{
    bool res = false;
    for(unsigned int i = 0; i < v.size(); i++){
        if(aristas[n][v[i]] == 1){
            res = true;
            break;
        }
    }
    return res;
}

bool Grafo::loContagian(const unsigned int n, const vector<unsigned int> &v) const{
    bool res = false;
    for(unsigned int i = 0; i < v.size(); i++){
        if(aristas[v[i]][n] == 1){
            res = true;
            break;
        }
    }
    return res;
}

void Grafo::borrarDuplicadosYnoMaximales(vector< vector<unsigned int> > &grupos){
    vector<unsigned int> ids;
    for(unsigned int i = 0; i < grupos.size() - 1; i++){
        for(unsigned int j = i + 1; j < grupos.size(); j++){
            unsigned int rel = relacion(grupos[i], grupos[j]);
            //rel == 0 entonces son distintos y ninguno incluido en el otro
            if(rel == 2){
                //son iguales
                if(!pertenece(j,ids)){
                    ids.push_back(j);
                }
            }
            else if(rel == 1){
                //grupos[j] incluido en grupos[i]
                if(!pertenece(j,ids)){
                    ids.push_back(j);
                }
            }
            else if(rel == 3){
                //grupos[i] incluido en grupos[j]
                if(!pertenece(i,ids)){
                    ids.push_back(i);
                }
            }
        }
    }

    for(unsigned int i = 0; i < ids.size(); i++){
        grupos.erase(grupos.begin() + ids[i]-i);
    }
}

unsigned int Grafo::relacion(const vector<unsigned int> &v1,const vector<unsigned int> &v2){
    unsigned int res = 2;
    for(unsigned int i = 0; i < v1.size();i++){
        if(!pertenece(v1[i],v2)){
            res--;
            break;
        }
    }
    for(unsigned int i = 0; i < v2.size();i++){
        if(!pertenece(v2[i],v1)){
            if(res == 2){
                res = 3;
            }
            else{
                res--;
            }
            break;
        }
    }
    return res;
}

