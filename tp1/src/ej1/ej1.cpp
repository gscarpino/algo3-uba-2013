
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


void mostrarVecInt(const vector<int> &x);
void resolverOrdTiempos(int cant, const vector<int> &p, const vector<int> &c);
void ordenarDesc(vector<int> &p, vector<int> &c);
int calcTiempo(const vector<int> &p, const vector<int> &c);

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


        istringstream sLinea(linea);

        for(int i = 0, n; i < cant; i++){
            sLinea >> n;
            p[i] = n;
        }

        getline(arch, linea);
        istringstream sLinea2(linea);

        for(int i = 0, n; i < cant; i++){
            sLinea2 >> n;
            c[i] = n;
        }

        cout << "Tiempo de produccion:";
        mostrarVecInt(p);
        cout << endl << "Tiempo de carga de combustible:";
        mostrarVecInt(c);

        //Se crea una copia de p y c para poder contrastar con
        // otras implementaciones
        resolverOrdTiempos(cant,p,c);


    }

    cout << endl << "Termino" << endl;
	return 0;
}

void mostrarVecInt(const vector<int> &x){
    cout << endl << "Vector: ";
    for(int i = 0; i < x.size(); i++){
        cout << x[i] << " ";
    }
}

void resolverOrdTiempos(int cant, const vector<int> &p, const vector<int> &c){
    vector<int> tp(p);
    vector<int> tc(c);

    ordenarDesc(tp,tc);

    calcTiempo(tp,tc);
}


void ordenarDesc(vector<int> &p, vector<int> &c){
    int temp;
    for(int i = 0; i < p.size()-1; i++){
        for(int j = i+1;j<p.size();j++){
            if(p[i] < p[j]){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
                temp = c[i];
                c[i] = c[j];
                c[j] = temp;
            }
//            // Ver si afecta el orden de tiempos de carga de
//            // combustible cuando empata tiempo de produccion
//            else if(p[i] == p[j]){
//                if(c[i] < c[j]){
//                    temp = p[i];
//                    p[i] = p[j];
//                    p[j] = temp;
//                    temp = c[i];
//                    c[i] = c[j];
//                    c[j] = temp;
//                }
//            }
        }
    }
}

int calcTiempo(const vector<int> &p, const vector<int> &c){
    int res = 0;
    vector<int> ejecucionInicio(p.size());
    vector<int> terminacion(p.size());

    ejecucionInicio[0] = c[0];
    terminacion[0] = ejecucionInicio[0] + p[0];
    for(int i = 1; i < ejecucionInicio.size(); i++){
        ejecucionInicio[i] = ejecucionInicio[i - 1] + c[i];
        terminacion[i] = ejecucionInicio[i] + p[i];
        if(res < terminacion[i]){
            res = terminacion[i];
        }
    }


    cout << endl << "RES: " << res << endl;

    return res;
}
