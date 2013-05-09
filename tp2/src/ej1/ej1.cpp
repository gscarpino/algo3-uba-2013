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
   unsigned int n = 7;
   Grafo grafo(n);
   //no usar nodo 0!!!
   grafo.agregarArista(1,5);
   grafo.agregarArista(1,3);
   grafo.agregarArista(5,3);
   grafo.agregarArista(5,4);
   grafo.agregarArista(5,2);
   grafo.agregarArista(3,4);
   grafo.agregarArista(3,2);
   grafo.agregarArista(4,6);
   grafo.agregarArista(2,6);
//   for(unsigned int i = 0; i< m ; i++)
//      grafo.agregarArista(a[i],b[i]);
//
//   // Creamos las aristas entre el nodo artificial y el resto de los nodos
   for(unsigned int i = 1; i< n ; i++)
      grafo.agregarArista(0,i);

   // dist[i] es la longitud del camino simple mas largo entre el nodo incial
   // y el nodo i
   vector<unsigned int> dist(n);

   // camino[i] = siguiente nodo en el camino mas largo desde i (0 indica fin)
   vector<unsigned int> camino(n);
   list<unsigned int> orden(n);
   unsigned int hijo;

    if(!grafo.ordenTopologico(0, orden)){
        cout << "Hay ciclo!" << endl;
    }
    return 0;
//   if(grafo.ordenTopologico(1, orden)){
//      for(uint i = n-1; i >= 0; i--){
//         uint v = orden[i];
//         dist[v-1] = 0;
//         camino[v-1] = 0; // Si el nodo no tiene hijos (no entra en el siguiente ciclo), es fin de camino.
//
//         // calculamos la distancia buscando la maxima distancia de los anteriores
//         for (uint j = 0; j < grafo.hijos(v).size(); j ++)
//            hijo = grafo.hijos(v)[j];
//            if((dist[hijo-1] + 1) > dist[v-1])
//            {
//               dist[v-1] = dist[hijo-1] + 1;
//               camino[v-1] =  hijo;
//            }
//      }
//
//      int maxDist;
//      for( uint i = 1; i < n; i++){
//         maxDist = (dist[i] > dist[i+1])? dist[i]: dist[i+1];
//      }
//
//      cout << maxDist;
//      uint i = 1;
//      while(camino[i] != 0)
//      {
//         i = camino[i-1];
//         cout << " " << i;
//      }
//      cout << endl;
//   }
//   else{
//      //el grafo contiene ciclos
//      cout << "Las cepas pueden mutar infinitamente";
//   }
//    return 0;

}
