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
        for(unsigned int i = 0; i < cantInv; i++){
            unsigned int temp;
            getline(inputFile, linea);
            istringstream sLinea(linea);
            sLinea >> contagiables;
            for(unsigned int j = 0; j < contagiables; j++){
                sLinea >> temp;
//                investigadores.agregarArista(make_pair(i,temp));
                investigadores.agregarArista(i,temp);
            }
        }

//        cout << "Investigadores: " << investigadores.getNodos() << endl;
//
        vector< vector< unsigned int > > gruposLineal(investigadores.grupoDeRiesgoMaximalesLineal());
        cout << "Cantidades de grupos de riesgo maximales: " << gruposLineal.size() << endl;
        for(unsigned int i = 0; i < gruposLineal.size(); i++){
            cout << "Grupo " << i << ": ";
            for(unsigned int j = 0; j < gruposLineal[i].size(); j++){
                cout << gruposLineal[i][j] << " ";
            }
            cout << endl;
        }


            cout << endl;
        vector< vector< unsigned int > > gruposNoLineal(investigadores.grupoDeRiesgoMaximalesNoLineal());
        cout << "Cantidades de grupos de riesgo maximales: " << gruposNoLineal.size() << endl;
        for(unsigned int i = 0; i < gruposNoLineal.size(); i++){
            cout << "Grupo " << i << ": ";
            for(unsigned int j = 0; j < gruposNoLineal[i].size(); j++){
                cout << gruposNoLineal[i][j] << " ";
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
//    cout << "Creando tests pocas rutas existentes." << endl;
//    ofstream outputFile("testsPocasRutasExistentes.txt",  ios_base::trunc);
//    if(!outputFile.is_open()){
//        cerr << "Error al abrir/crear el archivo de salida." << endl;
//        exit(1);
//    }
//    srand(time(NULL));
//    unsigned int maxNodos = 250;
//    unsigned int repeticiones = 50;
//    unsigned int costo;
////    bool existe;
//    for(unsigned int i = 4; i <= maxNodos; i++){
//        for(unsigned int r = 0; r < repeticiones; r++){
//            outputFile << i << endl;
//            for(unsigned int a = 0; a < i; a++){
//                for(unsigned int b = a+1; b < i; b++){
//                    costo = rand() % 10000 + 500;
//                    if(a==0 && b==1){
//                        outputFile << a << " " << b << " " << 1 << " " << costo << endl;
//                    }
//                    else{
//                        if(rand()%100 < 20){
//                            outputFile << a << " " << b << " " << 1 << " " << costo << endl;
//                        }
//                        else{
//                            outputFile << a << " " << b << " " << 0 << " " << costo << endl;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    outputFile << "#";
//    outputFile.close();
}
