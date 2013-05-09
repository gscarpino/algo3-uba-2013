#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Redefs.h"

#include "Camino.h"
#include "Grafo.h"

#define TESTING 0
#define RESULTADOS 1


using namespace std;

void genTests();
bool estaEn(const vector< Camino > &caminos, const Camino &c);

//timespec diff(timespec start, timespec end){
//        timespec temp;
//        if ((end.tv_nsec-start.tv_nsec)<0) {
//                temp.tv_sec = end.tv_sec-start.tv_sec-1;
//                temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
//        } else {
//                temp.tv_sec = end.tv_sec-start.tv_sec;
//                temp.tv_nsec = end.tv_nsec-start.tv_nsec;
//        }
//        return temp;
//}

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
        unsigned int cantCiudades = atoi(linea.c_str());

        Grafo ciudades(cantCiudades);
        unsigned int contRutasExistentes = 0;
        for(unsigned int i = 0; i < ((cantCiudades * (cantCiudades - 1))/2); i++){
            unsigned int c1,c2,e,p;
            getline(inputFile, linea);
            istringstream sLinea(linea);
            sLinea >> c1;
            sLinea >> c2;
            sLinea >> e;
            if(e) contRutasExistentes++;
            sLinea >> p;
            Camino c(c1,c2,e,p);
            ciudades.agregarArista(c);
        }

//        timespec comienzo;
//        timespec terminacion;
        if(RESULTADOS){
//            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
        }
        Grafo ciudadesModificadas(ciudades.AGM());
        if(RESULTADOS){
//            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);
//            archRes << cantCiudades << " " << contRutasExistentes << " " << diff(comienzo,terminacion).tv_nsec << endl;
        }

        if(ciudadesModificadas.cantAristas() == 0){
            cout << "Error" << endl;
            archRes.close();
            inputFile.close();
            outputFile.close();
            exit(1);
        }

        unsigned int costoTotal = 0;
        vector< Camino > caminos(ciudades.getAristas());
        for(unsigned int i = 0; i < caminos.size(); i++){
            caminos[i].imprimir();
            if(caminos[i].getExiste()){
                if(!estaEn(ciudadesModificadas.getAristas(),caminos[i])){
                    costoTotal = costoTotal + caminos[i].getCosto();
                }
            }
            else{
                if(estaEn(ciudadesModificadas.getAristas(),caminos[i])){
                    costoTotal = costoTotal + caminos[i].getCosto();
                }
            }
        }

        outputFile << costoTotal << " " << ciudadesModificadas.cantAristas();
        caminos = ciudadesModificadas.getAristas();
        cout << endl;
        for(unsigned int i = 0; i < caminos.size(); i++){
            caminos[i].imprimir();
            outputFile << " " << caminos[i].getCiudad1() << " " << caminos[i].getCiudad2();
        }


    }
    archRes.close();
    inputFile.close();
    outputFile.close();
    return 0;
}

bool estaEn(const vector< Camino > &caminos, const Camino &c){
    bool res = false;

    for(unsigned int i = 0; i < caminos.size();i++){
        if(caminos[i].getCiudad1() == c.getCiudad1() && caminos[i].getCiudad2() == c.getCiudad2()){
            res = true;
            break;
        }
        if(caminos[i].getCiudad1() == c.getCiudad2() && caminos[i].getCiudad2() == c.getCiudad1()){
            res = true;
            break;
        }
    }

    return res;
}

void genTests(){

    cout << "Creando tests pocas rutas existentes." << endl;
    ofstream outputFile("testsPocasRutasExistentes.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }
    srand(time(NULL));
    unsigned int maxNodos = 250;
    unsigned int repeticiones = 50;
    unsigned int costo;
//    bool existe;
    for(unsigned int i = 4; i <= maxNodos; i++){
        for(unsigned int r = 0; r < repeticiones; r++){
            outputFile << i << endl;
            for(unsigned int a = 0; a < i; a++){
                for(unsigned int b = a+1; b < i; b++){
                    costo = rand() % 10000 + 500;
                    if(a==0 && b==1){
                        outputFile << a << " " << b << " " << 1 << " " << costo << endl;
                    }
                    else{
                        if(rand()%100 < 20){
                            outputFile << a << " " << b << " " << 1 << " " << costo << endl;
                        }
                        else{
                            outputFile << a << " " << b << " " << 0 << " " << costo << endl;
                        }
                    }
                }
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Tests creados." << endl << endl;


    cout << "Creando tests muchas rutas existentes." << endl;
    outputFile.open("testsMuchasRutasExistentes.txt");
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }
    for(unsigned int i = 4; i <= maxNodos; i++){
        for(unsigned int r = 0; r < repeticiones; r++){
            outputFile << i << endl;
            for(unsigned int a = 0; a < i; a++){
                for(unsigned int b = a+1; b < i; b++){
                    costo = rand() % 10000 + 500;
                    if(a==0 && b==1){
                        outputFile << a << " " << b << " " << 1 << " " << costo << endl;
                    }
                    else{
                        if(rand()%100 < 70){
                            outputFile << a << " " << b << " " << 1 << " " << costo << endl;
                        }
                        else{
                            outputFile << a << " " << b << " " << 0 << " " << costo << endl;
                        }
                    }
                }
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Tests creados." << endl << endl;
}
