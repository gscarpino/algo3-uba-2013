#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <algorithm>

//typedef vector<unsigned int> vec;

using namespace std;


void  mostrarVecTuplaInt(const vector< pair<int,int> > &x);

int main(int argc, char *argv[]) {
cout << "Ejercicio 2 - Sensores defectuosos" << endl << endl;
    ifstream arch("input1.txt");
    if(!arch.is_open()){
        cerr << "Error al abrir el archivo." << endl;
    }

    string linea;

    while(!arch.eof()){
        getline(arch, linea);
        if(linea[0] == '#'){
            break;
        }

        istringstream sLinea(linea);

        unsigned int cant;
        vector< pair<int,int> > sensores;
        unsigned int medDefectuosa;
        unsigned int medicion = 0;

        int n; int i = 0;
        while(!sLinea.eof()){
            sLinea >> n;
            if(i == 0){
                cant = n;
                sensores.resize(cant);
                medicion = cant;
            }
            else if(i == 1){
                medDefectuosa = n;
            }
            else{
                sensores[i-2] = make_pair(n,n);
            }
            i++;
        }
        mostrarVecTuplaInt(sensores);

        return 0;
//        getline(arch, linea);
//        istringstream sLinea2(linea);
//
//        for(int i = 0, n; i < cant; i++){
//            sLinea2 >> n;
//            c[i] = n;
//        }
//
//        cout << "Tiempo de produccion:";
//        mostrarVecInt(p);
//        cout << endl << "Tiempo de carga de combustible:";
//        mostrarVecInt(c);
//
//        //Se crea una copia de p y c para poder contrastar con
//        // otras implementaciones
//        resolverOrdTiempos(cant,p,c);


    }

    cout << endl << "Termino" << endl;
        return 0;
}




void  mostrarVecTuplaInt(const vector< pair<int,int> > &x){
    cout << "[ ";
    for(int i = 0; i < x.size(); i++){
        cout << "(" << x[i].first << "," << x[i].second << ") ";
    }
    cout << "]";
}

