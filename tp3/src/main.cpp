#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <cmath>

#include "Grafo.h"
#include "exacto.h"
#include "goloso.h"
#include "local.h"
#include "grasp.h"

#define TESTING 0
#define RES_EFECTIVIDAD 0
#define RES_TIMING 0
#define RES_Goloso 0
#define RES_Grasp 0

using namespace std;

void genTests();

int main(int argc, char * argv[]){

    srand(time(NULL));
    if(TESTING){
        genTests();
        return 0;
    }

    cout << "Algoritmos y Estructuras de Datos III - 2013 C1" << endl;
    cout << "TP3: Coloreo y Maximo impacto" << endl << endl;


    if(argc <= 1) {
        cout << "Modo de uso: ej1 archivoEntrada archivoSalida" << endl;
        exit(1);
    }

    argv[1] = "input.in";
//    argv[1] = "testAzar.txt";
//    argv[1] = "GyHdensos.txt";
//    argv[1] = "conHcomplemento.txt";
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


    ofstream resEfect;
    ofstream resGoloso;
    ofstream resGrasp;
    if(RES_EFECTIVIDAD){
        resEfect.open("Resultado_Efectividad.csv",  ios_base::trunc);
        if(!resEfect.is_open()){
            cerr << "Error al abrir/crear el archivo de salida." << endl;
            exit(1);
        }
        resEfect << "Nodos Exacto Goloso BusquedaLocal Grasp" << endl;
    }

    if(RES_Goloso){
        resGoloso.open("Resultado_Goloso.csv",  ios_base::trunc);
        if(!resGoloso.is_open()){
            cerr << "Error al abrir/crear el archivo de salida." << endl;
            exit(1);
        }
        resGoloso << "Nodos Exacto 0 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9 0.95 1" << endl;
    }
    if(RES_Grasp){
        resGrasp.open("Resultado_Grasp.csv",  ios_base::trunc);
        if(!resGrasp.is_open()){
            cerr << "Error al abrir/crear el archivo de salida." << endl;
            exit(1);
        }
        resGrasp << "Nodos Exacto 0 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9 0.95 1" << endl;
    }


    unsigned int efectividadGoloso = 0;
    unsigned int efectividadGolosoAcertado = 0;

    unsigned int efectividadLocal = 0;
    unsigned int efectividadLocalAcertado = 0;

    unsigned int efectividadGrasp = 0;
    unsigned int efectividadGraspAcertado = 0;
    unsigned int cont = 0;

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
//        cout << "Nodos: " << nodos << " - Aristas G: " << aristasG << " - Aristas H: " << aristasH << endl;

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

        cont++;
        cout << endl << "N " << nodos << " R " << cont << endl;
        double porcentaje = 0.1;
//        vector<unsigned int> impactoExacto(maximoImpactoExacto(grafoG,grafoH));
//        cout << "*Exacto: " << impactoExacto[0] << "*";
        vector<unsigned int> impactoExacto2(maximoImpactoExacto2(grafoG,grafoH));
                cout << "*Exacto: " << impactoExacto2[0] << "*";
//        if(impactoExacto[0] != impactoExacto2[0]){
//            cout << "Exacto1: " << impactoExacto[0] << " - Exacto2: " << impactoExacto2[0] << endl;
//            cout << "Grafo G:" << endl;
//            grafoG.imprimir();
//            cout << "Grafo H:" << endl;
//            grafoH.imprimir();
//            cout << "Coloreo Exacto 1:" << endl;
//            mostrarColoreo(impactoExacto);
//            cout << endl << "Coloreo Exacto 2:" << endl;
//            mostrarColoreo(impactoExacto2);
//            exit(1);
//        }
        vector<unsigned int> impactoGoloso(maximoImpactoGoloso(grafoG,grafoH,porcentaje));
//        cout << "*Goloso: " << impactoGoloso[0] << "*";
        vector<unsigned int> impactoLocal(maximoImpactoLocal(grafoG,grafoH,impactoGoloso));
//        cout << "*Local: " << impactoLocal[0] << "*";
        vector<unsigned int> impactoGrasp(maximoImpactoGrasp(grafoG,grafoH,porcentaje));
//        cout << "*Grasp: " << impactoGrasp[0] << "*";
//        outputFile << impactoGoloso[0];
        cout << endl;
//        if(abs(impactoExacto[0]- impactoGoloso[0]) == 0) efectividadGolosoAcertado++;
//        if(abs(impactoExacto[0]- impactoGoloso[0]) <= 1) efectividadGoloso++;
//        if(abs(impactoExacto[0]- impactoLocal[0]) == 0) efectividadLocalAcertado++;
//        if(abs(impactoExacto[0]- impactoLocal[0]) <= 1) efectividadLocal++;
//        if(abs(impactoExacto[0]- impactoGrasp[0]) == 0) efectividadGraspAcertado++;
//        if(abs(impactoExacto[0]- impactoGrasp[0]) <= 1) efectividadGrasp++;
//        if(impactoGrasp[0] > impactoExacto[0]){
//            cout << "Error! Grasp: " << impactoGrasp[0] << " - Exacto: " << impactoExacto[0] << endl;
//            cout << "Grafo G:" << endl;
//            grafoG.imprimir();
//            cout << "Grafo H:" << endl;
//            grafoH.imprimir();
//            exit(1);
//        }
//         << " - Goloso: " << impactoGoloso[0] << endl;
//        for(unsigned int i = 1; i < impactoExacto.size(); i++){
//            cout << " " << impactoExacto[i];
//            outputFile << " " << impactoExacto[i];
//        }
//        cout << endl;
//        outputFile << endl;

        if(RES_EFECTIVIDAD){
//            resEfect << nodos << " " << impactoExacto[0] << " " << impactoGoloso[0] << " " << impactoLocal[0] << " " << impactoGrasp[0] << endl;
        }

        if(RES_Goloso){
//            resGoloso << nodos << " " << impactoExacto[0];
            for(unsigned int parametro = 0; parametro <= 100; parametro+=5){
                vector<unsigned int> impactoGoloso2(maximoImpactoGoloso(grafoG,grafoH,parametro/100.0));
                resGoloso << " " << impactoGoloso2[0];
            }
            resGoloso << endl;
        }
        if(RES_Grasp){
//            resGrasp << nodos << " " << impactoExacto[0];
            for(unsigned int parametro = 0; parametro <= 100; parametro+=5){
                vector<unsigned int> impactoGrasp2(maximoImpactoGrasp(grafoG,grafoH,parametro/100.0));
                resGrasp << " " << impactoGrasp2[0];
            }
            resGrasp << endl;
        }


    }

    cout << endl << "Efectividad Goloso: " << ((double)efectividadGoloso/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Goloso acertando: " << ((double)efectividadGolosoAcertado/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Local: " << ((double)efectividadLocal/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Local acertando: " << ((double)efectividadLocalAcertado/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Grasp: " << ((double)efectividadGrasp/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Grasp acertando: " << ((double)efectividadGraspAcertado/(double)cont) * 100 << "%" << endl;

    resEfect.close();
    resGoloso.close();

    cout << endl << "Termino" << endl;
    return 0;
}


void genTests(){


    ofstream outputFile;
    unsigned int minNodos = 8;
    unsigned int maxNodos = 8;
    unsigned int repeticiones = 100;
    int prob = 50;

    cout << "Creando test G y H al azar" << endl;
    outputFile.open("testAzar.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    for(unsigned int nodos = minNodos; nodos <= maxNodos; nodos++){
        for(unsigned int r = 0; r < repeticiones; r++){
            vector<pair<unsigned int, unsigned int> > vecinosG;
            vector<pair<unsigned int, unsigned int> > vecinosH;
            for(unsigned int i = 0; i < nodos; i++){
                for(unsigned int j = i+1; j < nodos; j++){
                    if(rand()%100 < prob){
                        vecinosG.push_back(make_pair(i+1,j+1));
                    }
                    if(rand()%100 < prob){
                        vecinosH.push_back(make_pair(i+1,j+1));
                    }
                }
            }
            outputFile << nodos << " " << vecinosG.size() << " " << vecinosH.size()<< endl;
            for(unsigned int i = 0; i < vecinosG.size(); i++){
                outputFile << vecinosG[i].first << " " << vecinosG[i].second << endl;
            }
            for(unsigned int i = 0; i < vecinosH.size(); i++){
                outputFile << vecinosH[i].first << " " << vecinosH[i].second << endl;
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Test creado." << endl;

    prob = 75;

    cout << "Creando test G y H densos" << endl;
    outputFile.open("GyHdensos.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    for(unsigned int nodos = minNodos; nodos <= maxNodos; nodos++){
        for(unsigned int r = 0; r < repeticiones; r++){
            vector<pair<unsigned int, unsigned int> > vecinosG;
            vector<pair<unsigned int, unsigned int> > vecinosH;
            for(unsigned int i = 0; i < nodos; i++){
                for(unsigned int j = i+1; j < nodos; j++){
                    if(rand()%100 < prob){
                        vecinosG.push_back(make_pair(i+1,j+1));
                    }
                    if(rand()%100 < prob){
                        vecinosH.push_back(make_pair(i+1,j+1));
                    }
                }
            }
            outputFile << nodos << " " << vecinosG.size() << " " << vecinosH.size()<< endl;
            for(unsigned int i = 0; i < vecinosG.size(); i++){
                outputFile << vecinosG[i].first << " " << vecinosG[i].second << endl;
            }
            for(unsigned int i = 0; i < vecinosH.size(); i++){
                outputFile << vecinosH[i].first << " " << vecinosH[i].second << endl;
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Test creado." << endl;

    prob = 50;

    cout << "Creando test H complemento de G" << endl;
    outputFile.open("conHcomplemento.txt",  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    for(unsigned int nodos = minNodos; nodos <= maxNodos; nodos++){
        for(unsigned int r = 0; r < repeticiones; r++){
            unsigned int cont = 0;
            vector<vector<bool> > vecinosG;

            for(unsigned int i = 0; i < nodos; i++){
                vector<bool> temp(nodos,false);
                vecinosG.push_back(temp);
                for(unsigned int j = i+1; j < nodos; j++){
                    if(rand()%100 < prob){
                        vecinosG[i][j] = true;
                        cont++;
                    }
                }
            }
            outputFile << nodos << " " << cont << " " << (nodos*nodos - nodos - cont*2)/2 << endl;
            for(unsigned int i = 0; i < nodos; i++){
                for(unsigned int j = i+1; j < nodos; j++){
                    if(vecinosG[i][j]){
                        outputFile << i+1 << " " << j+1 << endl;
                    }
                }
            }
            for(unsigned int i = 0; i < nodos; i++){
                for(unsigned int j = i+1; j < nodos; j++){
                    if(!vecinosG[i][j]){
                        outputFile << i+1 << " " << j+1 << endl;
                    }
                }
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Test creado." << endl;
}
