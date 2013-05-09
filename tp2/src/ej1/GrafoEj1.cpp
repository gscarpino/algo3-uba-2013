#include "GrafoEj1.h"
#include <stack>
#define BLANCO -1
#define GRIS 0
#define NEGRO 1


Grafo::Grafo(unsigned int cant){	//constructor vacio, requiere la cantidad de nodos que vamos a poner

	this->cantNodos=cant;		//cantidad de nodos

	vector<unsigned int> vacio;

	for(unsigned int i=0; i< cant; i++) {
		this->aristas.push_back(vacio);
      this->colores.push_back(BLANCO);
	}

	this->cantAristas=0;


}

Grafo::Grafo(const Grafo& other){ //constructor por copia

	this->cantNodos = other.cantNodos;
	this->aristas = other.aristas;
	this->cantAristas = other.cantAristas;
   this->colores= other.colores;

}


void Grafo::agregarArista(const unsigned int u, const unsigned int v){  //requiere u >0

	this->aristas[u-1].push_back(v);
	this->cantAristas++;

}

bool Grafo::tieneHijos (unsigned int nodo){ 	//requiere nodo>0  (en este ejercicio tiene sentido esperar nodo>0)

		return (this->aristas[nodo-1].empty());
}

unsigned int Grafo::cantidadNodos(){

	return cantNodos;
}

unsigned int Grafo::cantidadAristas(){

	return cantAristas;
}

vector<unsigned int> Grafo::hijos(unsigned int nodo){

	return this->aristas[nodo-1];
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
bool Grafo::ordenTopologico(unsigned int raiz, vector<unsigned int> &order)
{
      stack<unsigned int> S;
      S.push(1); // empezamos en el nodo inicial
      unsigned int t;
      while(!S.empty()){
         t = S.top();
         this->colores[t-1] = GRIS;
         S.pop();
         this->colores[t-1] = NEGRO;
         order.push_back(t);

         for(unsigned int u : this->hijos(t))
         {
            if (this->colores[u-1] == NEGRO)
            {
               return false; // Hay un ciclo, no es DAG
            }
            else if (this->colores[u-1] == BLANCO)
            {
               this->colores[u-1] = GRIS;
               S.push(u);
            }
         }
      }
      return true;
}

