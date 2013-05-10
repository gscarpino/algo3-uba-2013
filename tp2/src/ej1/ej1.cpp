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
 /*
      unsigned int a, b;

      unsigned int n = 9+1;
      Grafo grafo(n);
      //no usar nodo 0!!!
      grafo.agregarArista(1,2);
      grafo.agregarArista(3,2);
      grafo.agregarArista(3,4);
      grafo.agregarArista(3,5);
      grafo.agregarArista(2,4);
      grafo.agregarArista(4,5);
      grafo.agregarArista(3,1);

      grafo.agregarArista(6,7);
      grafo.agregarArista(7,8);
      grafo.agregarArista(8,9);
      //grafo.agregarArista(9,7);
*/

   uint n, m, u, v;


   string linea;
   while(!cin.eof()){
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

      // Creamos las aristas entre el nodo artificial y el resto de los nodos
      for(unsigned int i = 1; i< n ; i++)
         grafo.agregarArista(0,i);

      vector<unsigned int> camino(n); // camino[i] = siguiente nodo en el camino mas largo desde i (0 indica fin)
      vector<unsigned int> orden(n);

      int longitud = grafo.caminoMaximo(camino);

      cout << longitud;

      // Si existe un camino, lo mostramos
      if(longitud >= 0)
      {
         int i = 0;
         while(camino[i] != 0)
         {
            i = camino[i];
            cout << " " << i;
         }
         cout << endl;
      }
   }
   return 0;
}
