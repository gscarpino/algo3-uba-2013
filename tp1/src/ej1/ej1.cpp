
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>

//typedef vector<unsigned int> vec;

using namespace std;

int main() {
    cout << "Ejercicio 1 - La fabrica de quesos" << endl << endl;
    ifstream arch("input1.txt");
    if(!arch.is_open()){
        cerr << "Error al abrir el archivo." << endl;
    }

    string linea;

    while(!arch.eof()){
        getline(arch, linea);
        if(linea == "#"){
            break;
        }

        unsigned int cant = atoi(linea.c_str());

        vector<int> p(cant);
        vector<int> c(cant);

        getline(arch, linea);
        cout << "testing: " << linea << endl;

        char * pValores;

        cout << "Tiempo de produccion:" << endl;

        pValores = strtok(linea.c_str(),' ');
        p[0] = atoi(pValores[0].c_str());
        cout << p[0] << " ";
//        for(int i = 1; i < cant+4; i++){
//            p[i] = strtol(pEnd, NULL,10);
//            cout << p[i] << " ";
//        }
//
//        getline(arch, linea);
//
//
//
//        cout << endl << endl << "Tiempo de carga de combustible:" << endl;
//        c[0] = strtol(linea.c_str(), &pEnd,10);
//        cout << c[0] << " ";
//        for(int i = 1; i < cant+4; i++){
//            c[i] = strtol(pEnd, NULL,10);
//            cout << c[i] << " ";
//        }

    }

    cout << endl << "Termino" << endl;
	return 0;
}
