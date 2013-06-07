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
    uint n, m, u, v;

    string linea;
    while(!cin.eof())
    {
        /*Inicio de lectura de entrada*/
        cin >> linea;
        if(linea == "#")
        {
            break;
        }

        istringstream sLinea(linea);
        sLinea >> n; // cantidad de cepas (nodos)
        cin >> m; // cantidad de mutaciones (ejes orientados)

        Grafo grafo(n);

        for(uint i = 0; i < m; i++)
        {
            cin >> u >> v;
            grafo.agregarArista(u, v);
        }

        /*Fin de lectura de entrada*/

        vector<unsigned int> camino;

        int longitud = grafo.caminoMaximo(camino);

        // Descomentar la siguiente linea si se necesita mostar la longitud junto con el camino
        //cout << longitud;

        // Si existe un camino, lo mostramos
        if(longitud >= 0)
        {
            for(unsigned int i = 0; i < camino.size(); i++)
            {
                cout << camino[i] << " ";
            }

        }
        else
        {
            cout << "-1";
        }

        cout << endl;

    }
    return 0;
}
