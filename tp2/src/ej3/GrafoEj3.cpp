#include "GrafoEj3.h"


Grafo::Grafo(unsigned int cant){	//constructor vacio, requiere la cantidad de nodos que vamos a poner

	this->cantNodos=cant;		//cantidad de nodos

	vector<unsigned int> vacio;
	this->aristas.reserve(cant);
	this->indice.reserve(cant);
	this->bajoIndice.reserve(cant);



	for(unsigned int i=0; i< cant; i++) {
		this->aristas.push_back(vacio);
		this->indice.push_back(-1);
		this->bajoIndice.push_back(-1);
	}

	this->cantAristas=0;


}

Grafo::Grafo(const Grafo& other){ //constructor por copia

	this->cantNodos = other.cantNodos;
	this->cantAristas = other.cantAristas;
	this->aristas = other.aristas;
	this->indice = other.indice;
	this->bajoIndice = other.bajoIndice;

}


void Grafo::agregarArista(const unsigned int u, const unsigned int v){  //requiere u >0

	this->aristas[u].push_back(v);
	this->cantAristas++;

}



unsigned int Grafo::cantidadNodos(){
	return cantNodos;
}

unsigned int Grafo::cantidadAristas(){
	return cantAristas;
}

vector<unsigned int> Grafo::hijos(unsigned int nodo){
	return this->aristas[nodo];
}


vector<vector<unsigned int> > Grafo::grupoDeRiesgoMaximalesLineal(){
    vector<vector<unsigned int> > res(1);
    unsigned int index = 0;
    stack<unsigned int> pila;

    for(unsigned int i = 0; i < this->cantNodos; i++){
        if(indice[i] == -1){
            tarjanAlgorithm(index,pila,i,res);
        }
    }
    res.pop_back();
    return res;
}

void Grafo::tarjanAlgorithm(unsigned int &index, stack<unsigned int> &pila, unsigned int nodo, vector<vector<unsigned int> > &componentes){
    this->indice[nodo] = index;
    this->bajoIndice[nodo] = index;
    index++;
    pila.push(nodo);

    for(unsigned int i = 0; i < aristas[nodo].size(); i++){
        unsigned int nodo_temp = this->aristas[nodo][i];
        if(this->indice[nodo_temp] == -1){
            tarjanAlgorithm(index,pila,nodo_temp,componentes);
            this->bajoIndice[nodo] = min(this->bajoIndice[nodo],this->bajoIndice[nodo_temp]);
        }
        else{
            if(pertenecePila(pila,nodo_temp)){
                this->bajoIndice[nodo] = min(this->bajoIndice[nodo],this->indice[nodo_temp]);
            }
        }
    }

    if(this->bajoIndice[nodo] == this->indice[nodo]){
        while(nodo != pila.top()){
            componentes[componentes.size()-1].push_back(pila.top());
            pila.pop();
        }
        componentes[componentes.size()-1].push_back(pila.top());
        pila.pop();
        vector<unsigned int> temp;
        componentes.push_back(temp);
    }

}

bool Grafo::pertenecePila(stack<unsigned int> pila, unsigned int nodo){
    bool res = false;
    while(!pila.empty() && !res){
        if(pila.top() == nodo){
            res = true;
        }
        pila.pop();
    }
    return res;
}



vector< vector<unsigned int> > Grafo::grupoDeRiesgoMaximalesNoLineal(){
    vector< vector<unsigned int> > res;

    for(unsigned int i = 0; i < cantNodos; i++){
        vector<unsigned int> unitario(1,i);
        res.push_back(unitario);
    }

    for(unsigned int i = 0; i < cantNodos; i++){
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
        for(unsigned int j = 0; j < aristas[n].size(); j++){
            if(aristas[n][j] == v[i]){
                res = true;
                break;
            }
        }
    }
    return res;
}

bool Grafo::loContagian(const unsigned int n, const vector<unsigned int> &v) const{
    bool res = false;
    for(unsigned int i = 0; i < v.size(); i++){
        for(unsigned int j = 0; j < aristas[v[i]].size(); j++){
            if(aristas[v[i]][j] == n){
                res = true;
                break;
            }
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


