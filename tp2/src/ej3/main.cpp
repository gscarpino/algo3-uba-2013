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

//    argv[1] = "testsDigrafos500Nodos.txt";
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

//        cout << "Investigadores: " << investigadores.cantidadNodos() << endl;

        timespec comienzo;
        timespec terminacion;
        if(RESULTADOS){
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
        }
        vector< vector< unsigned int > > grupos(investigadores.grupoDeRiesgoMaximales());
        if(RESULTADOS){
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);
            archRes << investigadores.cantidadNodos() << " " << investigadores.cantidadAristas() << " " << diff(comienzo,terminacion).tv_nsec << endl;
        }
        outputFile << grupos.size() << endl;
        for(unsigned int i = 0; i < grupos.size(); i++){
            outputFile << grupos[i].size();
            for(unsigned int j = 0; j < grupos[i].size(); j++){
                outputFile << " " << grupos[i][j];
            }
            outputFile << endl;
        }





    }
    archRes.close();
    inputFile.close();
    outputFile.close();
    return 0;
}

void genTests(){
    cout << "Creando tests varios grupos de riesgos..." << endl;
    ofstream outputFile;
    srand(time(NULL));
    unsigned int maxNodos = 300;
    unsigned int repeticiones = 100;
    int prob = 50;
    unsigned int componentes = 3;

    outputFile.open("testsVariosGruposDeRiesgo.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    for(unsigned int i = 3; i <= maxNodos; i++){

        componentes = i / 10 + 1;

        for(unsigned int r = 0; r < repeticiones; r++){
            outputFile << i << endl;
            for(unsigned int minimo = 0; minimo < i; minimo = minimo + i/componentes){
                unsigned int tope = minimo + i/componentes;
                if(tope > i) tope = i;
                for(unsigned int a = minimo; a < tope; a++){
                    vector<unsigned int> vecinos;
                    for(unsigned int b = minimo; b < tope; b++){
                        if(b!=a){
                            if(rand()%100 < prob){
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
    }

    outputFile << "#";
    outputFile.close();
    cout << "Tests creados." << endl;

    maxNodos = 100;
    repeticiones = 1000;

    cout << "Creando tests digrafos completos..." << endl;
    outputFile.open("testsDigrafosCompletos.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    componentes = 1;
    for(unsigned int i = 3; i <= maxNodos; i++){


        for(unsigned int r = 0; r < repeticiones; r++){
            outputFile << i << endl;
            for(unsigned int minimo = 0; minimo < i; minimo = minimo + i/componentes){
                unsigned int tope = minimo + i/componentes;
                if(tope > i) tope = i;
                for(unsigned int a = minimo; a < tope; a++){
                    vector<unsigned int> vecinos;
                    for(unsigned int b = minimo; b < tope; b++){
                        if(b!=a){
                            vecinos.push_back(b);
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
    }

    outputFile << "#";
    outputFile.close();
    cout << "Tests creados." << endl;
    repeticiones = 100;

    cout << "Creando tests digrafos con 50 nodos..." << endl;
    outputFile.open("testsDigrafos50Nodos.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }


    maxNodos = 50;
    for(unsigned int aristas = 0; aristas < maxNodos - 1; aristas++){

        for(unsigned int r = 0; r < repeticiones; r++){
            outputFile << maxNodos << endl;
            for(unsigned int a = 0; a < maxNodos; a++){
                vector<unsigned int> vecinos;
                for(unsigned int arista = 0; arista < aristas; arista++){
                    if(a != (a + arista + 1)%maxNodos)   vecinos.push_back((a + arista + 1)%maxNodos);
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

    cout << "Creando tests digrafos con 500 nodos..." << endl;
    outputFile.open("testsDigrafos500Nodos.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }


    maxNodos = 250;
    for(unsigned int aristas = 0; aristas < maxNodos - 1; aristas++){
        for(unsigned int r = 0; r < repeticiones; r++){
            outputFile << maxNodos << endl;
            for(unsigned int a = 0; a < maxNodos; a++){
                vector<unsigned int> vecinos;
                for(unsigned int arista = 0; arista < aristas; arista++){
                    if(a != (a + arista + 1)%maxNodos)   vecinos.push_back((a + arista + 1)%maxNodos);
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
