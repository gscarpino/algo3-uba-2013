#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <time.h>

#define TESTING_AZAR 0
#define TESTING_PAREJO 0  //FALTA
#define RESULTADOS 1

using namespace std;

//********** TESTING *********
typedef struct timespec {
	time_t tv_sec; /* seconds */
	long tv_nsec; /* nanoseconds */
} tiempo;

timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

//********** TESTING *********



void  mostrarVecInt(const vector<int> &x){
    cout << "[ ";
    for(int i = 0; i < x.size(); i++){
//        cout << "(" << x[i].first << "," << x[i].second << ") ";
        cout << x[i] << " ";
    }
    cout << "]";
}
void  mostrarVecIntTupla(const vector<pair<int,int> > &x){
    cout << "[ ";
    for(int i = 0; i < x.size(); i++){
//        cout << "(" << x[i].first << "," << x[i].second << ") ";
        cout << "(" << x[i].first << "," << x[i].second << ") ";
    }
    cout << "]";
}

bool cmpHeap(const pair<int,int> &x, const pair<int, int> &y){

    if(y.second < x.second)
        return true;
    else if(y.second == x.second)
        return y.first < x.first;
    else
        return false;

}

int proxSensorHeap(vector<pair<int, int> > &tiempos,const vector<int> sensores){
    //Requiere tiempos este heapificado
    pair<int, int> sig;
    int res = 0;

    sig = tiempos.front();
    res = sig.first;
    sig.second = sig.second + sensores[res];
    pop_heap(tiempos.begin(),tiempos.end(),cmpHeap);
    tiempos.pop_back();
    tiempos.push_back(sig);
    push_heap(tiempos.begin(),tiempos.end(),cmpHeap);

    return res;
}

int main(int argc, char *argv[]) {

    cout << "Ejercicio 2 - Sensores defectuosos" << endl << endl;

    if(TESTING_AZAR){
        cout << "Creando tests..." << endl;
        int maxSensores = 100;
        int repeticiones = 1000;
        int minSensores = 10;
        int tiempo = 0;
        int falla = 0;
        ofstream archTesting("testingAzar.txt");
        if(archTesting.is_open()){
            srand(time(NULL));
            for(int s = minSensores; s < maxSensores;s++){
                for(int r = 0; r < repeticiones; r++){
                    falla = s * 20 + rand() % s + 1;
                    archTesting << s << " " << falla;
                    for(int i = 0; i < s; i++){
                        tiempo = 1 + rand() % 20;
                        archTesting << " " << tiempo;
                    }
                    archTesting << "\n";
                }
            }
        }
        archTesting << "#";
        archTesting.close();

        cout << "Tests creados." << endl;
        return 0;
    }

    if(TESTING_PAREJO){
        cout << "Creando tests..." << endl;
        int maxSensores = 100;
        int repeticiones = 1000;
        int minSensores = 50;
        int tiempo = 0;
        int falla = 0;
        ofstream archTesting("testingParejo.txt");
        if(archTesting.is_open()){
            srand(time(NULL));
            for(int s = minSensores; s < maxSensores;s++){
                for(int r = 0; r < repeticiones; r++){
                    falla = s + rand() % 500 + 1;
                    archTesting << s << " " << falla;
                    for(int i = 0; i < s; i++){
                        tiempo = 1 + rand() % 20;
                        archTesting << " " << tiempo;
                    }
                    archTesting << "\n";
                }
            }
        }
        archTesting << "#";
        archTesting.close();

        cout << "Tests creados." << endl;
        return 0;
    }


    if(argc <= 1) {
      cout << "Modo de uso: ej2 archivoEntrada archivoSalida";
      return 1;
    }
    argv[1] = "testingAzar.txt";
    ifstream arch(argv[1]);
    if(!arch.is_open()){
        cerr << "Error al abrir el archivo de entrada." << endl;
    }

    ofstream archSalida(argv[2],  ios_base::trunc);
    if(!archSalida.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
    }

    string linea;
    if(RESULTADOS){
        archSalida.close();
        archSalida.open("resultados.csv");
        archSalida << "Sensores;Falla;Sensor;Tiempo;" << endl;
    }

    unsigned int corrida = 1;
    while(!arch.eof()){
        getline(arch, linea);
        if(linea[0] == '#'){
            break;
        }

        istringstream sLinea(linea);

        unsigned int cant = 0;
        vector<int> sensores;
        vector<pair<int, int> > tiemposHeap;
        unsigned int medDefectuosa = 0;
        unsigned int medicion = 0;
        int proximoHeap = 0;
        vector<int> medicionesHeap;

        int n = 0; int i = 0;
        while(!sLinea.eof()){
            sLinea >> n;
            if(i == 0){
                cant = n;
                sensores.resize(cant);
                tiemposHeap.resize(cant);
                medicion = cant;
            }
            else if(i == 1){
                medDefectuosa = n;
            }
            else{
                sensores[i-2] = n;
                tiemposHeap[i-2] = make_pair(i-2,n);
                medicionesHeap.push_back(i-1);
            }
            i++;
        }

        tiempo comienzo;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
        make_heap(tiemposHeap.begin(),tiemposHeap.end(),cmpHeap);   //O(3*n)

//        cout << endl << "Inicio:" << endl;
//        mostrarVecIntTupla(tiemposHeap);
        while(medicion < medDefectuosa){            // k - n iteraciones
            proximoHeap = proxSensorHeap(tiemposHeap,sensores);
//            cout << endl << endl << "Medicion " << medicion << ":" << endl;
//            mostrarVecIntTupla(tiemposHeap);
            medicionesHeap.push_back(proximoHeap + 1);
            medicion++;
        }
        tiempo terminacion;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);

//        cout << endl << "Sol 1: ";
//        mostrarVecInt(mediciones);

//        cout << endl << "Mediciones: ";
//        mostrarVecInt(medicionesHeap);
//        cout << endl << "Sensor que fallo en la medicion " << medDefectuosa << ": " << medicionesHeap[medDefectuosa-1] << endl;
        cout << "Corrida " << corrida << endl;
        if(RESULTADOS){
            archSalida << cant << ";" << medDefectuosa << ";" << medicionesHeap[medDefectuosa-1] << ";" << difftime(comienzo,terminacion).tv_nsec << ";" << endl;
        }
        else{
            archSalida << "Sensor que fallo en la medicion " << medDefectuosa << ": " << medicionesHeap[medDefectuosa-1] << endl;
        }

        corrida++;

    }

    cout << endl << "Termino" << endl;
    arch.close();
    archSalida.close();
    return 0;
}






