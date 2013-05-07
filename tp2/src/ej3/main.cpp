#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Grafo.h"

#define TESTING 0
#define RESULTADOS 1

void genTests();

using namespace std;

int main(int argc, char * argv[]){

    if(TESTING){
        genTests();
        return 0;
    }

    if(argc <= 1) {
        cout << "Modo de uso: ej1 archivoEntrada archivoSalida" << endl;
        exit(1);
    }

//    argv[1] = "testsPocasRutasExistentes.txt";

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
    ofstream archRes;
    if(RESULTADOS){
        archRes.open("resultado.csv");
        archRes << "Nodos AristasExistentes Tiempo" << endl;
    }

    string linea;
    while(!inputFile.eof()){
        getline(inputFile, linea);
        if(linea == "#"){
            break;
        }
        unsigned int cantInv = atoi(linea.c_str());

        Grafo investigadores(cantInv);
        unsigned int contagiables = 0;
        unsigned int aa = 0;
        for(unsigned int i = 0; i < cantInv; i++){
            unsigned int temp;
            getline(inputFile, linea);
            istringstream sLinea(linea);
            sLinea >> contagiables;
            for(unsigned int j = 0; j < contagiables; j++){
                sLinea >> temp;
                investigadores.agregarArista(make_pair(i,temp));
            }
        }

        cout << "Investigadores: " << investigadores.getNodos() << endl;
        cout << "Cant aristas: " << investigadores.cantAristas() << endl;

        vector<unsigned int> grupo(investigadores.grupoDeRiesgo());
        cout << "Cantidad del grupo de riesgo: " << grupo.size() << endl;
        for(unsigned int i = 0; i < grupo.size(); i++){
            cout << grupo[i] << " ";
        }

//        timespec comienzo;
//        timespec terminacion;
//        if(RESULTADOS){
//            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
//        }
////        Grafo ciudadesModificadas(ciudades.AGM());
//        if(RESULTADOS){
//            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);
//            archRes << cantCiudades << " " << contRutasExistentes << " " << diff(comienzo,terminacion).tv_nsec << endl;
//        }

    }
    archRes.close();
    inputFile.close();
    outputFile.close();
    return 0;
}

void genTests(){

}
