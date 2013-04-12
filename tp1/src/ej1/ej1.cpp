#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <algorithm>
#include <time.h>

#define TIEMPOS

using namespace std;
timespec diff(timespec start, timespec end);

string mostrarVecInt(const vector<int> &x);
void resolver(const vector<int> &in_p, const vector<int> &in_c, vector<int> &out_i, int &out_tiempo);
int calcTiempo(const vector<int> &p, const vector<int> &c, const vector<int> &orden);

void crearTest(int n){
        cout << "Creando tests..." << endl;
        ofstream archTesting("test.txt");

        if(archTesting.is_open()){
            srand(time(NULL));
            for(int i = 1; i <= n ; i++){
                  archTesting << i << "\n";
                  for(int j= 0; j < i; j++){
                     int tiempo = 1 + rand() %200;
                     archTesting  << tiempo << " ";
                  }
                  archTesting << endl;
                  for(int j= 0; j < i; j++){
                     int tiempo = 1 + rand() %200;
                     archTesting  << tiempo << " ";
                  }
                  archTesting << endl;
            }
        archTesting << "#";
        archTesting.close();

        cout << "Tests creados." << endl;
      }
}

int main(int argc, char *argv[]) {

    if(argc <= 1) {
      cout << "Modo de uso: ej1 archivoEntrada archivoSalida" << endl;
#ifdef TIEMPOS
      cout << "Para crear archivo de prueba: ej1 n, donde n es la cantidad de casos (casos de 1 a n maquinas con tiempos aleatorios).";
#endif
      return 0;
    }

#ifdef TIEMPOS
    if(argc == 2) {
      crearTest(atoi(argv[1]));
      return 0;
    }
#endif
    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cerr << "Error al abrir el archivo de entrada." << endl;
        return -1;
    }

    ofstream outputFile(argv[2],  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
         return -1;
    }

#ifdef TIEMPOS
      ofstream timeFile(string(argv[1]) + "_tiempos", ios_base::trunc);
       if(!timeFile.is_open()){
           cerr << "Error al abrir el archivo de registro de tiempos." << endl;
       };
#endif
   string linea;
   int tiempoMinimo;


   cout << "Algoritmos y Estructuras de Datos III - 2013 C1" << endl << "TP1 - Ejercicio 1: La fabrica de quesos" << endl << endl;

    while(!inputFile.eof()){
        getline(inputFile, linea);
        if(linea == "#"){
            break;
        }

        unsigned int cant = atoi(linea.c_str());

        vector<int> p(cant);
        vector<int> c(cant);
        vector<int> orden(cant);

        getline(inputFile, linea);
        istringstream sLinea(linea);
        for(unsigned int i = 0, n; i < cant; i++){
            sLinea >> n;
            p[i] = n;
        }

        getline(inputFile, linea);
        istringstream sLinea2(linea);
        for(unsigned int i = 0, n; i < cant; i++){
            sLinea2 >> n;
            c[i] = n;
        }

       // cout << "Tiempo de produccion          : " << mostrarVecInt(p) << endl;
       // cout << "Tiempo de carga de combustible: " << mostrarVecInt(c) << endl;

#ifdef TIEMPOS
      timespec comienzo;
      timespec terminacion;
      long tiempo = 0;
      for(int t = 0; t < 1000; t++){
         clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
#endif

        resolver(p,c, orden, tiempoMinimo);

#ifdef TIEMPOS
         clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);
         tiempo += diff(comienzo,terminacion).tv_nsec;
      }
      tiempo = tiempo / 1000;
      timeFile << cant << " " << tiempo << endl;

#endif

        for(auto maquina : orden)
            outputFile << maquina << " ";

        outputFile << tiempoMinimo << endl;
    }

   inputFile.close();
   outputFile.close();

#ifdef TIEMPOS
   timeFile.close();
#endif
   cout << endl << "Termino" << endl;
	return 0;
}

string  mostrarVecInt(const vector<int> &x){
    ostringstream oss;
    for(auto elem: x){
        oss << elem << " ";
    }
    return oss.str();
}


void resolver(const vector<int> &in_p, const vector<int> &in_c, vector<int> &out_orden, int &out_tiempo){
   int cant = in_p.size();
   vector< pair<int, int> > maquinas(cant);

   // Creamos una lista con tuplas (P_i, i)
   for(int i = 0; i < cant; i++)
      maquinas.push_back(make_pair(in_p[i], i));

   // Ordenamos la lista de manera decreciente, segun los P_i
   sort(maquinas.begin(), maquinas.end(), greater<pair<int, int> > ());

   // Generamos el vector que contiene el orden en que se deben llenar las maquinas
   for(int i = 0;  i  < cant; i++) out_orden[i] = maquinas[i].second;

   // El ordenamiento del vector out_orden puede realizarse sin necesidad de crear
   // un vector de tuplas (maquinas), haciendo un sort indirecto por medio de una
   // funcion lambda (como se muestra a continuacion), resultando en una constante
   // oculta menor, ademas de un menor footprint:
   //iota(out_orden.begin(), out_orden.end(), 0); // esta linea llena la lista out_orden con out_orden[i] = i
   //sort(out_orden.begin(), out_orden.end(),[&in_p](int i, int j){return in_p[i] >= in_p[j];});

   // Calculamos cual es el tiempo que tardan en terminar todas las maquinas
   out_tiempo = calcTiempo(in_p, in_c, out_orden);

   return;
}


int calcTiempo(const vector<int> &p, const vector<int> &c, const vector<int> &orden){
    int res = 0, inicio = 0, t_i = 0;

    for(int i : orden){
        t_i = inicio + c[i] + p[i];
        if(res < t_i) res = t_i;
        inicio = inicio + c[i];
    }

    //cout << "Tiempo: " << res << endl;
    return res;
}

//********** TESTING *********

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

