#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include "GrafoEj1.h"

#define RESULTADOS 1
#define uint unsigned int

using namespace std;

timespec diff(timespec start, timespec end){
        timespec temp;
        if ((end.tv_nsec-start.tv_nsec)<0) {
                temp.tv_sec = end.tv_sec-start.tv_sec-1;
                temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
        } else {
                temp.tv_sec = end.tv_sec-start.tv_sec;
                temp.tv_nsec = end.tv_nsec-start.tv_nsec;
        }
        return temp;
}

int main()
{
    uint n, m, u, v;

	ofstream archRes;
    if(RESULTADOS){
        archRes.open("resultado.csv");
        archRes << "x Tiempo" << endl;
    }
	
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
		
		timespec comienzo;
        timespec terminacion;
        if(RESULTADOS){
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
        }
		
        int longitud = grafo.caminoMaximo(camino);

		if(RESULTADOS){
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);
            archRes << grafo.cantNodos()  << " " << diff(comienzo,terminacion).tv_nsec << endl;
        }
        
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
