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
#define ABIERTO 0
#define DESCUBIERTO 1
#define CERRADO 2
#define uint unsigned int
class Grafo{

	public:
      Grafo(unsigned int cant);
      Grafo(const Grafo& other);
      void agregarArista(const unsigned int u, const unsigned int v); //agrega la arista dirigida
      unsigned int cantidadNodos();
      unsigned int cantidadAristas();
      vector<unsigned int> hijos(unsigned int nodo);
      vector<unsigned int> padres(unsigned int nodo);
      bool ordenTopologico(vector<unsigned int> &nodosOrdenados);
      int caminoMaximo(vector<unsigned int> &camino);
      vector<unsigned int> marcas;

	private:
      unsigned int cantNodos;
      vector< vector<unsigned int> > aristas;
      unsigned int cantAristas;
      bool visitar(const unsigned int nodo, list<unsigned int> &nodosOrdenados);
      int buscarNodoAbierto();

};

#endif // GRAFO_H
