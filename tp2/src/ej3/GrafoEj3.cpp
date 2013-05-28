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


vector<vector<unsigned int> > Grafo::grupoDeRiesgoMaximales(){
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
