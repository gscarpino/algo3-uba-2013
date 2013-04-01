#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define NEGRO 0;
#define BLANCO 1;

using namespace std;

typedef vector<unsigned int> Vec;
typedef vector<Vec> Matriz;

//Seguro hay que modificar esto
void resolver(const Matriz &tablero,const int dimN, const int dimM, const vector<Matriz> &piezas);
bool subPiezasDe(const int cantidad,const Matriz &tablero,const int dimN, const int dimM, const vector<Matriz> &piezas);

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

        //fruta
        resolver(tablero,dimN,dimM,piezas);
    }

    inputFile.close();
    outputFile.close();
    return 0;
}


//
void resolver(const Matriz &tablero,const int dimN, const int dimM, const vector<Matriz> &piezas){
    int cantidad = 1;
    bool haySol = false;
    while((!haySol) && (cantidad <= piezas.size())){
        //buscar generar todos los subconjuntos de 'cantidad' de piezas
        haySol = subPiezasDe(cantidad,tablero,dimN,dimM,piezas);
        cantidad++;
    }

    if(haySol){
        cout << "Se encontro solucion para esta instancia del problema con " << cantidad << " piezas." << endl;
    }
    else{
        cout << "No existe solucion para esta instancia del problema." << endl;
    }
}


bool subPiezasDe(const int cantidad,const Matriz &tablero,const int dimN, const int dimM, const vector<Matriz> &piezas){
    bool res =  false;
    return res;
}
