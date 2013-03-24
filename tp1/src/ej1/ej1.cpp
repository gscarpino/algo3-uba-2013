
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

typedef vector<unsigned int> vec;

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

        vec p();
        vec c();

        getline(arch, linea);

        strtok();
    }

    cout << endl << "Termino" << endl;
	return 0;
}
