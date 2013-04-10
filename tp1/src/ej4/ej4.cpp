#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "Redefs.h"
#include "Tablero.h"
#include "Pieza.h"




//Seguro hay que modificar esto
Solucion buscarSol(const Matriz &tablero,const int dimN, const int dimM, const vector<Pieza> &piezas);
vector< vector<Pieza> > subConjuntosDeTam(const vector<Pieza> &piezas, int tamanio);
bool esSolucion(const vector<Pieza> &piezas, const Matriz &tablero, const int dimN, const int dimM, Solucion &sol);
bool cubreExactoElTablero(const vector<Pieza> &piezas, const Matriz &tablero,const int dimN, const int dimM);
vector<int> pasarBinario(int n);
bool resolverJuego(vector<Pieza> piezas, Tablero tablero, Solucion &sol);


void imprimirMatriz(const Matriz &m){
    for(unsigned int i = 0; i < m.size(); i++){
        for(unsigned int j = 0; j < m[0].size(); j++){
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

        vector<Pieza> piezas;
        int id = 0;
        for(int i = 0; i < cantPiezas; i++){
            getline(inputFile, linea);
            istringstream sLinea2(linea);
            int piezaN,piezaM;
            sLinea2 >> piezaN;
            sLinea2 >> piezaM;
            Matriz forma;
            Vec fila2(piezaM);
            for(int j = 0; j < piezaN; j++){
                getline(inputFile, linea);
                istringstream sLinea3(linea);
                for(int k = 0; k < piezaM; k++){
                    sLinea3 >> n;
                    fila2[k] = n;
                }
                forma.push_back(fila2);

            }
            Pieza pieza(forma,id);
            id++;
            piezas.push_back(pieza);
        }

        cout << "N: " << dimN << " - M: " << dimM << " - Piezas: " << cantPiezas << endl << endl;
        cout << "Tablero: " << endl << endl;;
        imprimirMatriz(tablero);
        cout << endl << endl << "Piezas: " << endl;
        for(int i = 0; i < cantPiezas; i++){
            cout << endl << "- - -" << endl;
            piezas[i].imprimir();
            cout << "- - -" << endl;
        }


        Solucion solucion = buscarSol(tablero,dimN,dimM,piezas);
        cout << "Tamanio de la solucion final: " << solucion.size() << endl;
        cout << "[";
        for(unsigned int i = 0; i < solucion.size(); i++){
            solucion[i].imprimir();
        }
        cout << "]" << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}


Solucion buscarSol(const Matriz &tablero,const int dimN, const int dimM, const vector<Pieza> &piezas){
    Solucion res;
    bool haySol = false;
    for(unsigned int i = 1; i <= piezas.size(); i++){
        vector< vector<Pieza> > subConjuntos;

        subConjuntos = subConjuntosDeTam(piezas,i);

        for(unsigned int j = 0; j < subConjuntos.size(); j++){
                if(esSolucion(subConjuntos[j],tablero,dimN,dimM,res)){
                    haySol = true;
                    break;
                }
        }

        if(haySol){
            break;
        }
    }
    return res;
}


vector< vector<Pieza> > subConjuntosDeTam(const vector<Pieza> &piezas, int tamanio){
    vector< vector<Pieza> > res;
    unsigned int tope = pow(2,piezas.size());
    vector<int> numBin;
    unsigned int valor = 1;
    int sumaParcial = 0;

    while(valor < tope){
        vector<Pieza> subConj;
        numBin = pasarBinario(valor);

        for(unsigned int i = 0; i < numBin.size();i++){
            sumaParcial = sumaParcial + numBin[i];
        }

        if(sumaParcial == tamanio){

            for(unsigned int i = 0; i < numBin.size();i++){
                if(numBin[numBin.size() - i - 1]){
                    subConj.push_back(piezas[i]);
                }
            }
            res.push_back(subConj);

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


bool esSolucion(const vector<Pieza> &piezas, const Matriz &tablero,const int dimN, const int dimM, Solucion &sol){
    bool res = false;
    vector<Pieza> copiaPiezas = piezas;

    //cubreExactoElTablero poda pero no siempre son solucion

    Tablero copiaTableroFija(tablero,dimN,dimM);
    if(copiaTableroFija.cubreTodo(piezas)){

        Tablero copiaTablero = copiaTableroFija;
        res = resolverJuego(copiaPiezas,copiaTablero,sol);

        //hacer para que recorrar todas las posibles permutaciones
        while(next_permutation(copiaPiezas.begin(),copiaPiezas.end()) && !res){

            copiaTablero = copiaTableroFija;
            res = resolverJuego(copiaPiezas,copiaTablero,sol);
        }
    }
    return res;
}


bool resolverJuego(vector<Pieza> piezas, Tablero tablero, Solucion &sol){
    bool res;
    if(piezas.size() == 0){
        res = tablero.completo();
        if(res){
            sol = tablero.obtenerPiezas();
        }
    }
    else{
        Pieza sigPieza(piezas.back());
        piezas.pop_back();

        Pieza sigPieza2 = sigPieza.rotar();
        Pieza sigPieza3 = sigPieza2.rotar();
        Pieza sigPieza4 = sigPieza3.rotar();
        vector<Posicion> posiciones;

        posiciones = tablero.posiblesPosiciones(sigPieza);
        for(auto p : posiciones){
            Tablero nuevoTablero(tablero);
            nuevoTablero.ubicarFicha(sigPieza,0,p);
            res = resolverJuego(piezas,nuevoTablero,sol);
            if(res) break;
        }

        if(sigPieza != sigPieza2){
            posiciones = tablero.posiblesPosiciones(sigPieza2);
            for(auto p : posiciones){
                Tablero nuevoTablero(tablero);
                nuevoTablero.ubicarFicha(sigPieza2,1,p);
                res = resolverJuego(piezas,nuevoTablero,sol);
                if(res) break;
            }

            posiciones = tablero.posiblesPosiciones(sigPieza3);
            for(auto p : posiciones){
                Tablero nuevoTablero(tablero);
                nuevoTablero.ubicarFicha(sigPieza3,2,p);
                res = resolverJuego(piezas,nuevoTablero,sol);
                if(res) break;
            }

            posiciones = tablero.posiblesPosiciones(sigPieza4);
            for(auto p : posiciones){
                Tablero nuevoTablero(tablero);
                nuevoTablero.ubicarFicha(sigPieza4,3,p);
                res = resolverJuego(piezas,nuevoTablero,sol);
                if(res) break;
            }

        }


    }
    return res;
}







