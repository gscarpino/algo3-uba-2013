#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "Grafo.h"
#include "exacto.h"

using namespace std;

int main(int argc, char * argv[]){

    cout << "Algoritmos y Estructuras de Datos III - 2013 C1" << endl;
    cout << "TP3: Coloreo y Maximo impacto" << endl << endl;


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

    string linea;
    while(!inputFile.eof()){
        getline(inputFile, linea);
        if(linea == "#"){
            break;
        }
        unsigned int nodos;
        unsigned int aristasG;
        unsigned int aristasH;
        istringstream sLinea(linea);
        sLinea >> nodos;
        Grafo grafoG(nodos);
        Grafo grafoH(nodos);
        sLinea >> aristasG;
        sLinea >> aristasH;
        cout << "Nodos: " << nodos << " - Aristas G: " << aristasG << " - Aristas H: " << aristasH << endl;

        for(unsigned int i = 0; i < aristasG; i++){
            getline(inputFile, linea);
            istringstream sAristas(linea);
            unsigned int nodo1;
            unsigned int nodo2;
            sAristas >> nodo1;
            sAristas >> nodo2;
//            cout << "Nodo 1: " << nodo1 << " - Nodo 2: " << nodo2 << endl;
            grafoG.agregarArista(nodo1-1,nodo2-1);
        }

        for(unsigned int i = 0; i < aristasH; i++){
            getline(inputFile, linea);
            istringstream sAristas(linea);
            unsigned int nodo1;
            unsigned int nodo2;
            sAristas >> nodo1;
            sAristas >> nodo2;
//            cout << "Nodo 1: " << nodo1 << " - Nodo 2: " << nodo2 << endl;
            grafoH.agregarArista(nodo1-1,nodo2-1);
        }

        vector<unsigned int> impactoExacto(maximoImpactoExacto(grafoG,grafoH));
        outputFile << impactoExacto[0];
        for(unsigned int i = 1; i < impactoExacto.size(); i++){
            outputFile << " " << impactoExacto[i];
        }
        outputFile << endl;

    }

    cout << endl << "Termino" << endl;
    return 0;
}
