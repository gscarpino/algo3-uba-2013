#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "GrafoEj1.h"

#define uint unsigned int

using namespace std;

int main()
{
   // Vamos a trabajar con un grafo con un nodo extra
   // Solo debemos recordarlo al momento de generar la salida
   uint n = 7 + 1 ;
   uint m = 6;

   uint a[] = {1,3,4,5,7,3};
   uint b[] = {2,4,5,6,6,5};
   Grafo grafo(n);
   for(uint i = 0; i< m ; i++)
      grafo.agregarArista(a[i]+1,b[i]+1);

   // Creamos las aristas entre el nodo artificial y el resto de los nodos
   for(uint i = 2; i<= n ; i++)
      grafo.agregarArista(1,i);

   // dist[i] es la longitud del camino simple mas largo entre el nodo incial
   // y el nodo i
   vector<uint> dist(n);

   // camino[i] = siguiente nodo en el camino mas largo desde i (0 indica fin)
   vector<uint> camino(n);
   vector<uint> orden(n);
   uint hijo;

   if(grafo.ordenTopologico(1, orden)){
      for(uint i = n-1; i >= 0; i--){
         uint v = orden[i];
         dist[v-1] = 0;
         camino[v-1] = 0; // Si el nodo no tiene hijos (no entra en el siguiente ciclo), es fin de camino.

         // calculamos la distancia buscando la maxima distancia de los anteriores
         for (uint j = 0; j < grafo.hijos(v).size(); j ++)
            hijo = grafo.hijos(v)[j];
            if((dist[hijo-1] + 1) > dist[v-1])
            {
               dist[v-1] = dist[hijo-1] + 1;
               camino[v-1] =  hijo;
            }
      }

      int maxDist;
      for( uint i = 1; i < n; i++){
         maxDist = (dist[i] > dist[i+1])? dist[i]: dist[i+1];
      }

      cout << maxDist;
      uint i = 1;
      while(camino[i] != 0)
      {
         i = camino[i-1];
         cout << " " << i;
      }
      cout << endl;
   }
   else{
      //el grafo contiene ciclos
      cout << "Las cepas pueden mutar infinitamente";
   }

}
