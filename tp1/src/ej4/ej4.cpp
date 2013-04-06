#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>


#define NEGRO 0;
#define BLANCO 1;

using namespace std;

typedef vector<unsigned int> Vec;
typedef vector<Vec> Matriz;

//Seguro hay que modificar esto
vector<Matriz> buscarSol(const Matriz &tablero,const int dimN, const int dimM, const vector<Matriz> &piezas);
vector< vector<Matriz> > subConjuntosDeTam(const vector<Matriz> &piezas, int tamanio);
bool esSolucion(const vector<Matriz> &piezas, const Matriz &tablero,const int dimN, const int dimM);

vector<int> pasarBinario(int n);

void imprimirMatriz(const Matriz &m){
    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m[0].size(); j++){
            if(m[i][j]){
                cout << " BLANCO ";
            }
            else{
                cout << " NEGRO  ";
            }
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {

    if(argc <= 1) {
      cout << "Modo de uso: ej1 archivoEntrada archivoSalida";
      return 0;
    }

    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cerr << "Error al abrir el archivo de entrada." << endl;
    }

    ofstream outputFile(argv[2],  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
    }

    string linea;

    while(!inputFile.eof()){
        getline(inputFile, linea);
        if(linea == "#"){
            break;
        }

        istringstream sLinea(linea);
        int n;
        int temp = 0;
        int dimN,dimM,cantPiezas;
        while(!sLinea.eof()){
            sLinea >> n;
            if(temp == 0){
                dimN = n;
            }
            else if(temp == 1){
                dimM = n;
            }
            else if(temp == 2){
                cantPiezas = n;
            }
            else{
                cout << "ERROR LEYENDO ENTRADA" << endl;
                return 1;
            }
            temp++;
        }
        Vec fila(dimM);
        Matriz tablero;
        for(int i = 0; i < dimN; i++){
            getline(inputFile, linea);
            istringstream sLinea2(linea);
            for(int j = 0; j < dimM; j++){
                sLinea2 >> n;
                fila[j] = n;
            }
            tablero.push_back(fila);
        }

        vector<Matriz> piezas;

        for(int i = 0; i < cantPiezas; i++){
            getline(inputFile, linea);
            istringstream sLinea2(linea);
            int piezaN,piezaM;
            sLinea2 >> piezaN;
            sLinea2 >> piezaM;
            Matriz pieza;
            Vec fila2(piezaM);
            for(int j = 0; j < piezaN; j++){
                getline(inputFile, linea);
                istringstream sLinea3(linea);
                for(int k = 0; k < piezaM; k++){
                    sLinea3 >> n;
                    fila2[k] = n;
                }
                pieza.push_back(fila2);

            }
            piezas.push_back(pieza);
        }

        cout << "N: " << dimN << " - M: " << dimM << " - Piezas: " << cantPiezas << endl << endl;
        cout << "Tablero: " << endl << endl;;
        imprimirMatriz(tablero);
        cout << endl << endl << "Piezas: " << endl;
        for(int i = 0; i < cantPiezas; i++){
            cout << endl << "- - -" << endl;
            imprimirMatriz(piezas[i]);
            cout << "- - -" << endl;
        }


        vector<Matriz> solucion = buscarSol(tablero,dimN,dimM,piezas);
    }

    inputFile.close();
    outputFile.close();
    return 0;
}


vector<Matriz> buscarSol(const Matriz &tablero,const int dimN, const int dimM, const vector<Matriz> &piezas){
    vector<Matriz> res;
    for(int i = 1; i <= piezas.size(); i++){
        vector< vector<Matriz> > subConjuntos;

        cout << endl << "SubConjuntos de " << i << " piezas: " << endl;

        subConjuntos = subConjuntosDeTam(piezas,i);
        for(int j = 0; j < subConjuntos.size(); j++){
            if(esSolucion(subConjuntos[j],tablero,dimN,dimM)){
                res = subConjuntos[j];
                j = subConjuntos.size();
            }
        }

        cout << endl << "*************************" << endl;
        if(res.size() > 0){
            i = piezas.size() + 1;
        }
    }
    return res;
}


vector< vector<Matriz> > subConjuntosDeTam(const vector<Matriz> &piezas, int tamanio){
    vector< vector<Matriz> > res;
    unsigned int tope = pow(2,piezas.size());
    vector<int> numBin;
    unsigned int valor = 1;
    int sumaParcial = 0;
    vector<Matriz> subConj;
    while(valor < tope){
        numBin = pasarBinario(valor);



        for(int i = 0; i < numBin.size();i++){
            sumaParcial = sumaParcial + numBin[i];
        }

        if(sumaParcial == tamanio){

            cout << endl << "aaa" << endl;
            for(int i = 0; i < numBin.size();i++){
                if(numBin[numBin.size() - i - 1]){
                    cout << endl << "---" << endl;
                    subConj.push_back(piezas[i]);
                    imprimirMatriz(piezas[i]);
                    cout << endl << "---" << endl;
                }
            }

            res.push_back(subConj);
            cout << endl << "aaa" << endl;
        }
        valor++;
        sumaParcial = 0;
    }
    return res;
}

vector<int> pasarBinario(int n){
    vector<int> res;
    int temp;

    while(n > 0){
       temp = n % 2;
       n = n / 2;
       res.push_back(temp);
    }

    reverse(res.begin(),res.end());

    return res;
}


bool esSolucion(const vector<Matriz> &piezas, const Matriz &tablero,const int dimN, const int dimM){
    bool res = false;

    return res;
}
