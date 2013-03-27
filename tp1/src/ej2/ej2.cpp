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


void  mostrarVecInt(const vector<int> &x);

int proxSensor(const vector<int> &tiempos){
    int res = 0;
    int minimo = tiempos[0];
    for(int i = 0; i < tiempos.size(); i++){
        if(tiempos[i] < minimo){
            res = i;
            minimo = tiempos[i];
        }
    }
    return res;
}

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
        vector<int> sensores;
        vector<int> tiempos;
        unsigned int medDefectuosa;
        unsigned int medicion = 0;
        int proximo = 0;
        vector<int> mediciones;

        int n; int i = 0;
        while(!sLinea.eof()){
            sLinea >> n;
            if(i == 0){
                cant = n;
                sensores.resize(cant);
                tiempos.resize(cant);
                medicion = cant;
            }
            else if(i == 1){
                medDefectuosa = n;
                cout << "Medicion defectuosa: " << medDefectuosa << endl;
            }
            else{
                sensores[i-2] = n;
                tiempos[i-2] = n;
                mediciones.push_back(i-1);
            }
            i++;
        }

        mostrarVecInt(tiempos);
        while(medicion < medDefectuosa){
            proximo = proxSensor(tiempos);
            tiempos[proximo] = tiempos[proximo] + sensores[proximo];
            mostrarVecInt(tiempos);
            mediciones.push_back(proximo+1);
            medicion++;
        }



        mostrarVecInt(mediciones);


    }

    cout << endl << "Termino" << endl;
        return 0;
}




void  mostrarVecInt(const vector<int> &x){
    cout << "[ ";
    for(int i = 0; i < x.size(); i++){
//        cout << "(" << x[i].first << "," << x[i].second << ") ";
        cout << x[i] << " ";
    }
    cout << "]";
}

