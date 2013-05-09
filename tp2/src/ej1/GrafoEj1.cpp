#include "GrafoEj1.h"


Grafo::Grafo(unsigned int cant){	//constructor vacio, requiere la cantidad de nodos que vamos a poner

	this->cantNodos=cant;		//cantidad de nodos

	vector<unsigned int> vacio;
	this->aristas.reserve(cant);

	for(unsigned int i=0; i< cant; i++) {
		this->aristas.push_back(vacio);
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

bool Grafo::tieneHijos (unsigned int nodo){ 	//requiere nodo>0  (en este ejercicio tiene sentido esperar nodo>0)

		return !(this->aristas[nodo].empty());
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

vector<unsigned int> Grafo::padres(unsigned int nodo){

	vector<unsigned int> res;
	unsigned int tam=this->cantNodos;
	unsigned int j=0;

	for (unsigned int i=0; i< tam; i++){

		j=this->aristas[i].size();

		for(unsigned int f=0; f<j; f++){

			if(this->aristas[i][j]==nodo){
				res.push_back(i+1);
				break;
			}
		}
	}

	return res;
}

//Si el grafo es DAG, devuelve true y en el parametro de salida devuielve los nodos en orden topologico
// raiz: nodo considerado como raiz
// order: parametro de salida. valido solo si la funcion retorna true
//       order[i] = nodo en la posicion i correspondiente al orden topologico lineal
bool Grafo::ordenTopologico(unsigned int raiz, list<unsigned int> &nodosOrdenados)
{
      //0: novisitado, 1: marca temporal, 2: marca permanente
      vector<unsigned int> nodosMarcados(cantNodos,0);
      int seleccionado = 0;
      while(seleccionado != -1){
        seleccionado = buscarNodoNoMarcado(nodosMarcados);
        if(seleccionado != -1){
            if(!visitar(seleccionado,nodosMarcados,nodosOrdenados)){
                return false;
            }
        }
      }
      list<unsigned int> copiaOrden(nodosOrdenados);
      cout << "Orden: " << endl;
      for(unsigned int i = 0; i < copiaOrden.size();i++){
        cout << copiaOrden.front() << " ";
        copiaOrden.pop_front();
      }
      cout << endl;
      return true;
}

bool Grafo::visitar(const unsigned int nodo, vector<unsigned int> &nodosMarcados,list<unsigned int> &nodosOrdenados){
    if(nodosMarcados[nodo] == 1){
        //termino
        return false;
    }
    else if(nodosMarcados[nodo] == 0){
        nodosMarcados[nodo] = 1;
        for(unsigned int i = 0; i < this->aristas[nodo].size(); i++){
            if(!visitar(aristas[nodo][i],nodosMarcados,nodosOrdenados)){
                return false;
            }
        }
        nodosMarcados[nodo] = 2;
        nodosOrdenados.push_front(nodo);
    }
    return true;
}


int Grafo::buscarNodoNoMarcado(const vector<unsigned int> &nodosMarcados){
    int res = -1;
    for(unsigned int i = 0; i < nodosMarcados.size(); i++){
        if(nodosMarcados[i] == 0){
            res = i;
        }
    }
    return res;
}
