#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "Grafo.h"


using namespace std;

int main(int argc, char * argv[])
{
    if(argc <= 1) {
        cout << "Modo de uso: ej1 archivoEntrada archivoSalida" << endl;
        exit(1);
    }

    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cerr << "Error al abrir el archivo de entrada." << endl;
        exit(1);
    }

    ofstream outputFile(argv[2],  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    cout << "Algoritmos y Estructuras de Datos III - 2013 C1" << endl << "TP2 - Ejercicio 2: Reconfiguracion de rutas." << endl << endl;

    string linea;

    while(!inputFile.eof()){
        getline(inputFile, linea);
        if(linea == "#"){
            break;
        }
        unsigned int cantCiudades = atoi(linea.c_str());

        Grafo ciudades(cantCiudades);

        for(unsigned int i = 0; i < ((cantCiudades * (cantCiudades - 1))/2); i++){
            unsigned int c1,c2,e,p;
            getline(inputFile, linea);
            istringstream sLinea(linea);
            sLinea >> c1;
            sLinea >> c2;
            sLinea >> e;
            sLinea >> p;
            ciudades.agregarArista(c1,c2,make_pair(e,p));
        }

        Grafo ciudadesModificadas = ciudades.AGM();

    }

    return 0;
}
