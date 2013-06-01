#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "GrafoEj3.h"

#define TESTING 0
#define RESULTADOS 0

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

    argv[1] = "input.txt";
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

    cout << "Algoritmos y Estructuras de Datos III - 2013 C1" << endl << "TP2 - Ejercicio 3: Reconfiguracion de rutas." << endl << endl;
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
        for(unsigned int i = 0; i < cantInv; i++){
            unsigned int temp;
            getline(inputFile, linea);
            istringstream sLinea(linea);
            sLinea >> contagiables;
            for(unsigned int j = 0; j < contagiables; j++){
                sLinea >> temp;
                investigadores.agregarArista(i,temp);
            }
        }

//        cout << "Investigadores: " << investigadores.getNodos() << endl;
//
        vector< vector< unsigned int > > grupos(investigadores.grupoDeRiesgoMaximales());
        cout << "Cantidades de grupos de riesgo maximales: " << grupos.size() << endl;
        for(unsigned int i = 0; i < grupos.size(); i++){
//            cout << "Grupo " << i << "(" << grupos[i].size() << "): ";
            cout << "Grupo " << i << ": ";
            for(unsigned int j = 0; j < grupos[i].size(); j++){
                cout << grupos[i][j] << " ";
            }
            cout << endl;
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
    cout << "Creando tests..." << endl;
    ofstream outputFile("tests.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }
    srand(time(NULL));
    unsigned int maxNodos = 200;
    unsigned int repeticiones = 100;

    for(unsigned int i = 4; i <= maxNodos; i++){
        for(unsigned int r = 0; r < repeticiones; r++){
            outputFile << i << endl;
            for(unsigned int a = 0; a < i; a++){
                vector<unsigned int> vecinos;
                for(unsigned int b = 0; b < i; b++){
                    if(b!=a){
                        if(rand()%100 < 5){
                            vecinos.push_back(b);
                        }
                    }
                }
                outputFile << vecinos.size();
                for(unsigned int k = 0; k < vecinos.size(); k++){
                    outputFile << " " << vecinos[k];
                }
                outputFile << endl;
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Tests creados." << endl;
}
