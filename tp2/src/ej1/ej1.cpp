#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include "GrafoEj1.h"

#define uint unsigned int

using namespace std;

int main()
{
   // Vamos a trabajar con un grafo con un nodo extra
   // Solo debemos recordarlo al momento de generar la salida

   uint n, m, u, v;
   
   string linea;
   while(!cin.eof()){
   /*Inicio de lectura de entrada*/
	   cin >> linea;
      if(linea == "#")
         { break; }

      istringstream sLinea(linea);
      sLinea >> n; // cantidad de cepas (nodos)
      cin >> m; // cantidad de mutaciones (ejes orientados)

      n += 1;

      Grafo grafo(n);

      for(int i = 0; i < m; i++){
         cin >> u >> v;
         grafo.agregarArista(u, v);
      }

	/*Fin de lectura de entrada*/
	
	// Creamos las aristas entre el nodo artificial y el resto de los nodos
	for(unsigned int i = 1; i< n ; i++)
		grafo.agregarArista(0,i);

	vector<unsigned int> camino; 
	vector<unsigned int> orden(n);

	int longitud = grafo.caminoMaximo(camino);

	cout << longitud;

	// Si existe un camino, lo mostramos
	if(longitud >= 0)
	{
		for(unsigned int i = 0; i < camino.size(); i++){
			cout << " " << camino[i];
		}
		cout << endl;
	}
	}
	return 0;
}
