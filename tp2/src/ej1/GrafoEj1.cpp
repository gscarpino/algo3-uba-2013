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
bool Grafo::ordenTopologico(unsigned int raiz, vector<unsigned int> &nodosOrdenados)
{
      vector<unsigned int> colores(cantNodos,BLANCO);
      list<unsigned int> nodosOrdenadosTemp(cantNodos);
      int seleccionado = 0;

      while(seleccionado != -1){
         seleccionado = buscarNodoBlanco(colores);
         if(seleccionado != -1){
            if(!visitar(seleccionado,colores,nodosOrdenadosTemp)){
               return false;
            }
         }
      }

      for(unsigned int i = 0; i < nodosOrdenadosTemp.size();i++){
        nodosOrdenados[i] = (nodosOrdenadosTemp.front());
        nodosOrdenadosTemp.pop_front();
      }
      return true;
}

bool Grafo::visitar(const unsigned int nodo, vector<unsigned int> &colores,list<unsigned int> &nodosOrdenados){
    if(colores[nodo] == GRIS){
        //termino
        return false;
    }
    else if(colores[nodo] == BLANCO){
        colores[nodo] = GRIS;
        for(unsigned int i = 0; i < this->aristas[nodo].size(); i++){
            if(!visitar(aristas[nodo][i],colores,nodosOrdenados)){
                return false;
            }
        }
        colores[nodo] = NEGRO;
        nodosOrdenados.push_front(nodo);
    }
    return true;
}


int Grafo::buscarNodoBlanco(const vector<unsigned int> &nodosMarcados){
    int res = -1;
    for(unsigned int i = 0; i < nodosMarcados.size(); i++){
        if(nodosMarcados[i] == 0){
            res = i;
        }
    }
    return res;
}

unsigned int Grafo::caminoMaximo(vector<unsigned int> &camino){
   int n = this->cantNodos;
   vector<unsigned int> orden(n);
   // dist[i] es la longitud del camino simple mas largo entre el nodo incial
   // y el nodo i
   vector<uint> dist(n);
   uint hijo;

   if(this->ordenTopologico(0, orden)){
      for(int i = n-1; i >= 0; i--){
         uint v = orden[i];
         dist[v] = 0;
         camino[v] = 0; // Si el nodo no tiene hijos (no entra en el siguiente ciclo), es fin de camino.

         // calculamos la distancia buscando la maxima distancia de los anteriores
         for (unsigned int j = 0; j < (this->aristas[v]).size(); j++){
            hijo = this->aristas[v][j];
            if((dist[hijo] + 1) > dist[v])
               {
               dist[v] = dist[hijo] + 1;
               camino[v] =  hijo;
               }
            }
      }

      uint maxDist = dist[0] - 1; // Restamos el eje que une los nodos con el nodo inicial artificial
      return maxDist;
   }
   else
   {
      return -1;
   }
}
