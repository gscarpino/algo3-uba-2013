#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

/*----------------------- DISCLAIMER:---------------------------------
*
* Esta implementacion se basa fuertemente en el ejercicio 1 del tp.
* Por lo tanto,por ejemplo, no se provee manera de quitar un nodo.
*
*---------------------------------------------------------------------*/
#define BLANCO 0
#define GRIS 1
#define NEGRO 2
#define uint unsigned int
class Grafo{

	public:
      Grafo(unsigned int cant);
      Grafo(const Grafo& other);
      void agregarArista(const unsigned int u, const unsigned int v); //agrega la arista dirigida
      bool tieneHijos (unsigned int nodo); //para saber si es terminal
      unsigned int cantidadNodos();
      unsigned int cantidadAristas();
      vector<unsigned int> hijos(unsigned int nodo);
      vector<unsigned int> padres(unsigned int nodo);
      bool ordenTopologico(unsigned int nodo, vector<unsigned int> &nodosOrdenados);
      unsigned int caminoMaximo(vector<unsigned int> &camino);

	private:
      unsigned int cantNodos;
      vector< vector<unsigned int> > aristas;
      unsigned int cantAristas;
      bool visitar(const unsigned int nodo, vector<unsigned int> &nodosMarcados,list<unsigned int> &nodosOrdenados);
      int buscarNodoBlanco(const vector<unsigned int> &nodosMarcados);
};

#endif // GRAFO_H
