#include "GrafoEj3.h"


Grafo::Grafo(unsigned int cant){	//constructor vacio, requiere la cantidad de nodos que vamos a poner

	this->cantNodos=cant;		//cantidad de nodos

	vector<unsigned int> vacio;
	this->aristas.reserve(cant);

	

	for(unsigned int i=0; i< cant; i++) {
		this->aristas.push_back(vacio);
		this->index.push_back(-1);
		this->lowIndex.push_back(-1);
	}

	this->cantAristas=0;


}

Grafo::Grafo(const Grafo& other){ //constructor por copia

	this->cantNodos = other.cantNodos;
	this->aristas = other.aristas;
	this->cantAristas = other.cantAristas;

}


void Grafo::agregarArista(const unsigned int u, const unsigned int v){  //requiere u >0

	this->aristas[u].push_back(v);
	this->cantAristas++;

}

/*bool Grafo::tieneHijos (unsigned int nodo){ 	//requiere nodo>0  (en este ejercicio tiene sentido esperar nodo>0)

		return !(this->aristas[nodo].empty());
}*/

unsigned int Grafo::cantidadNodos(){
	return cantNodos;
}

unsigned int Grafo::cantidadAristas(){
	return cantAristas;
}

vector<unsigned int> Grafo::hijos(unsigned int nodo){
	return this->aristas[nodo];
}



vector<vector<unsigned int> >Grafo::resolver(){

	stack<unsigned int> s;
	vector<vector<unsigned int> > list;
	int indice=0;
	vector<unsigned int> closed (this->cantNodos,0);
	this.tarjanAlgorithm(0,list,s,indice, closed);

	for(int i=0; i<list.size; i++){ 	//tengo que sacar el nodo virtual que agregue (el nodo 0)

		if(list[i].size==1){

			if	(list[0]==0){

				list.erase(list.begin()+i);
			}

		}

	}

	return list;

}



void Grafo::tarjanAlgorithm(unsigned int nodo,vector<vector<unsigned int> > &list, stack<unsigned int> &s, int &indice, vector<unsigned int> closed){

	this->index[nodo]=indice; 		//acá ya lo marco como visitado
	this->lowIndex[nodo]=indice;
	indice++;

	s.push(nodo);

	for(int i=0; i<this->aristas[nodo].size();i++){
		int hijo = this->aristas[nodo][i];
		if(this->index[hijo]==-1){ //si el hijo no habia sido visitado
			tarjanAlgorithm(hijo,list,s,indice);	
			this->lowIndex[nodo]=min(this->lowIndex[nodo], this->lowIndex[hijo]);	//actualizo el lowIndex del padre;
		}
		else {

			if(closed[hijo]==0){
				this->lowIndex[nodo]=min(this->lowIndex[nodo], this->index[hijo]);
			}
		}
	}

	if (this->lowIndex[nodo]==this->index[nodo]){

		vector<unsigned int> componente;
		unsigned int n=s.pop();
		closed[n]=1;
		componente.push_back(n);

		while(n != nodo){
			unsigned int n=s.pop();
			closed[n]=1;
			componente.push_back(n);
		}

		list.push_back(componente);



	}

}