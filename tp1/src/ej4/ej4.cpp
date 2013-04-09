#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Sol.h"


#define NEGRO 0;
#define BLANCO 1;

using namespace std;

typedef vector<unsigned int> Vec;
typedef vector<Vec> Matriz;
typedef pair<int,Matriz > Pieza; //1er tupla el di
typedef pair<int,int> Posicion;
typedef vector<vector<pair<int,bool> > > Tablero;
typedef vector< Sol >  Solucion; //Arreglar esto

//Seguro hay que modificar esto
Solucion buscarSol(const Matriz &tablero,const int dimN, const int dimM, const vector<Pieza> &piezas);
vector< vector<Pieza> > subConjuntosDeTam(const vector<Pieza> &piezas, int tamanio);
bool esSolucion(const vector<Pieza> &piezas, const Matriz &tablero, const int dimN, const int dimM, Solucion &sol);
bool cubreExactoElTablero(const vector<Pieza> &piezas, const Matriz &tablero,const int dimN, const int dimM);
vector<int> pasarBinario(int n);
bool resolverJuego(vector<Pieza> &piezas, Tablero &tablero,const int dimN, const int dimM, Solucion &sol);
Tablero armarTablero(const Matriz &tablero,const int dimN, const int dimM);
bool cmpPieza(const Pieza &a, const Pieza &b);
bool esTableroCompleto(const Tablero &tablero,const int dimN, const int dimM);
bool rotar(Pieza &pieza);
vector<Posicion> posiblesPosiciones(const Pieza &pieza, const Tablero &tablero,const int dimN, const int dimM);
void ocuparFicha(const Pieza &pieza, const Posicion &pos, Tablero &tablero);
bool encaja(const Pieza &pieza, const Posicion &pos, const Tablero &tablero, const int dimN, const int dimM);

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

void imprimirPiezas(const vector<Pieza> &vm){
    cout << "Piezas: " << endl;
    for(int i = 0; i < vm.size(); i++){
        cout << "Pieza " << vm[i].first << endl;
    }
    cout << endl;
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
            Pieza pieza = make_pair(id,forma);
            id++;
            piezas.push_back(pieza);
        }

        cout << "N: " << dimN << " - M: " << dimM << " - Piezas: " << cantPiezas << endl << endl;
        cout << "Tablero: " << endl << endl;;
        imprimirMatriz(tablero);
        cout << endl << endl << "Piezas: " << endl;
        for(int i = 0; i < cantPiezas; i++){
            cout << endl << "- - -" << endl;
            imprimirMatriz(piezas[i].second);
            cout << "- - -" << endl;
        }


        Solucion solucion = buscarSol(tablero,dimN,dimM,piezas);
    }

    inputFile.close();
    outputFile.close();
    return 0;
}


Solucion buscarSol(const Matriz &tablero,const int dimN, const int dimM, const vector<Pieza> &piezas){
    Solucion res;
    bool haySol = false;
//    int inf = 0;
//    int sup = piezas.size();
//    int medio;
    //Se podria llegar a mejorar con busqueda binaria pero cambiar las podas
//    while(inf <= sup){
//        medio = (sup + inf) / 2;
    for(unsigned int i = 1; i <= piezas.size(); i++){
        vector< vector<Pieza> > subConjuntos;

        cout << endl << "SubConjuntos de " << i << " piezas: " << endl;



        subConjuntos = subConjuntosDeTam(piezas,i);

        for(unsigned int j = 0; j < subConjuntos.size(); j++){
                if(esSolucion(subConjuntos[j],tablero,dimN,dimM,res)){
                    haySol = true;
                    break;
                }
//            cout << "aaa" << endl;
//            for(int k = 0; k < subConjuntos[j].size(); k++){
//                cout  << "---" << endl;
//                imprimirMatriz(subConjuntos[j][k].second);
//                cout << endl << "---" << endl;
//            }
//
//            cout << "aaa" << endl;
        }

        if(haySol){
                cout << "Se encontro sol" << endl;
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
//            sort(subConj.begin(),subConj.end(),[](Matriz &a,Matriz &b){return (a.size() * a[0].size() > b.size() * b[0].size());});
//            sort(subConj.begin(),subConj.end(),cmpPieza);
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
    //requiere piezas ordenadas de mayor a menor segun area

    bool res = false;
    Tablero copiaTablero;
    vector<Pieza> permPiezas = piezas;
    vector<Pieza> copiaPiezas = permPiezas;
    //cubreExactoElTablero poda pero no siempre son solucion

    if(cubreExactoElTablero(piezas,tablero,dimN,dimM)){
        copiaTablero = armarTablero(tablero,dimN,dimM);

        cout << "Tam de piezas: " << copiaPiezas.size() << endl;
//        imprimirPiezas(copiaPiezas);
        res = resolverJuego(copiaPiezas,copiaTablero,dimN,dimM,sol);
        int marce = 1;

        //hacer para que recorrar todas las posibles permutaciones
        while(next_permutation(permPiezas.begin(),permPiezas.end()) && !res){
//                cout << "Marce " << marce << endl;
        marce++;
            copiaPiezas = permPiezas;
//            imprimirPiezas(copiaPiezas);
            copiaTablero = armarTablero(tablero,dimN,dimM);
            res = resolverJuego(copiaPiezas,copiaTablero,dimN,dimM,sol);
        }
    }

    return res;
}

bool cubreExactoElTablero(const vector<Pieza> &piezas, const Matriz &tablero,const int dimN, const int dimM){
    bool res = true;
//    int total = dimM * dimN;
//
//    for(unsigned int i = 0; i < piezas.size(); i++){
//        total = total - (piezas[i].second.size() * piezas[i].second[0].size());
//    }
//
//    res = (total == 0);

    return res;
}

bool cmpPieza(const Pieza &a, const Pieza &b){
    return (a.second.size() * a.second[0].size() > b.second.size() * b.second[0].size());
}

bool resolverJuego(vector<Pieza> &piezas, Tablero &tablero,const int dimN, const int dimM, Solucion &sol){
    bool res;
    if(piezas.size() == 0){
        res = esTableroCompleto(tablero,dimN,dimM);
    }
    else{
        Pieza sigPieza = piezas.back();
        piezas.pop_back();

        Pieza sigPieza2,sigPieza3,sigPieza4,sigPiezaTemp = sigPieza;
        vector<Posicion> posiciones;
//
//        if(rotar(sigPiezaTemp)){
//            sigPieza2 = sigPiezaTemp;
//            rotar(sigPiezaTemp);
//            sigPieza3 = sigPiezaTemp;
//            rotar(sigPiezaTemp);
//            sigPieza4 = sigPiezaTemp;
//
//            posiciones = posiblesPosiciones(sigPieza,tablero,dimN,dimM);
//            for(auto p : posiciones){
//                Tablero nuevoTablero = tablero;
//                ocuparFicha(sigPieza,p,nuevoTablero);
//                vector<Pieza> copiaPiezas = piezas;
//                Solucion nuevaSol;
//                Sol s(sigPieza.first,0,p);
//                nuevaSol.push_back(s); //Faltaria poner rotacion y sacar la forma
//                res = resolverJuego(copiaPiezas,nuevoTablero,dimN,dimM,nuevaSol);
//            }
//
//            if(!res){
//                posiciones = posiblesPosiciones(sigPieza2,tablero,dimN,dimM);
//                for(auto p : posiciones){
//                    Tablero nuevoTablero = tablero;
//                    ocuparFicha(sigPieza2,p,nuevoTablero);
//                    vector<Pieza> copiaPiezas = piezas;
//                    Solucion nuevaSol;
//                    Sol s(sigPieza2.first,1,p);
//                    nuevaSol.push_back(s);
//                    res = resolverJuego(copiaPiezas,nuevoTablero,dimN,dimM,nuevaSol);
//                }
//            }
//
//
//            if(!res){
//                posiciones = posiblesPosiciones(sigPieza3,tablero,dimN,dimM);
//                for(auto p : posiciones){
//                    Tablero nuevoTablero = tablero;
//                    ocuparFicha(sigPieza3,p,nuevoTablero);
//                    vector<Pieza> copiaPiezas = piezas;
//                    Solucion nuevaSol;
//                    Sol s(sigPieza3.first,2,p);
//                    nuevaSol.push_back(s);
//                    res = resolverJuego(copiaPiezas,nuevoTablero,dimN,dimM,nuevaSol);
//                }
//            }
//
//
//            if(!res){
//                posiciones = posiblesPosiciones(sigPieza4,tablero,dimN,dimM);
//                for(auto p : posiciones){
//                    Tablero nuevoTablero = tablero;
//                    ocuparFicha(sigPieza4,p,nuevoTablero);
//                    vector<Pieza> copiaPiezas = piezas;
//                    Solucion nuevaSol;
//                    Sol s(sigPieza4.first,3,p);
//                    nuevaSol.push_back(s);
//                    res = resolverJuego(copiaPiezas,nuevoTablero,dimN,dimM,nuevaSol);
//                }
//            }
//
//        }else{
            posiciones = posiblesPosiciones(sigPieza,tablero,dimN,dimM);
            for(auto p : posiciones){
                Tablero nuevoTablero = tablero;
                ocuparFicha(sigPieza,p,nuevoTablero);
                vector<Pieza> copiaPiezas = piezas;
                Solucion nuevaSol;
                Sol s(sigPieza.first,0,p);
                nuevaSol.push_back(s);
                res = resolverJuego(copiaPiezas,nuevoTablero,dimN,dimM,nuevaSol);
//            }
        }


    }
    return res;
}

Tablero armarTablero(const Matriz &tablero,const int dimN, const int dimM){
    Tablero res;
    vector<pair<int, bool> > fila(dimM);
    for(int i = 0; i < dimN; i++){
        for(int j = 0; j < dimM; j++){
            fila[j] = make_pair(tablero[i][j],false);
        }
        res.push_back(fila);
    }
    return res;
}

bool rotar(Pieza &pieza){
    Pieza res;
    Matriz forma;
    Vec fila(pieza.second.size());

    for(unsigned int i = 0; i < pieza.second[0].size(); i++){
        for(unsigned int j = 0; j < pieza.second.size(); j++){
            fila[j] = pieza.second[j][i];
        }
        forma.push_back(fila);
    }

    res = make_pair(pieza.first,forma);

    if(res != pieza){
        pieza = res;
        return true;
    }
    else{
        return false;
    }
}

bool esTableroCompleto(const Tablero &tablero,const int dimN, const int dimM){
    bool res = true;
    for(int i = 0; i < dimN; i++){
        for(int j = 0; j < dimM; j++){
            res = res && tablero[i][j].second;
        }
    }
    return res;
}

vector<Posicion> posiblesPosiciones(const Pieza &pieza, const Tablero &tablero, const int dimN, const int dimM){
    vector<Posicion> posiciones;
    Posicion p;

    for(int i = 0; i < dimN; i++){
        for(int j = 0; j < dimM; j++){
            p = make_pair(i,j);
            if(encaja(pieza,p,tablero,dimN,dimM)){
                posiciones.push_back(p);
            }
        }
    }
    return posiciones;
}

bool encaja(const Pieza &pieza, const Posicion &pos, const Tablero &tablero, const int dimN, const int dimM){
    bool res = true;
    for(unsigned int i = 0; i < pieza.second.size(); i++){
        for(unsigned int j = 0; j < pieza.second[0].size(); j++){
            if(((pos.first + i) < dimN) && ((pos.second + j) < dimM) && (res)){
                res = res && (tablero[pos.first + i][pos.second + j].first == pieza.second[i][j]) && (!tablero[pos.first + i][pos.second + j].second);
            }
            else{
                return false;
            }
        }
    }
    return res;
}

void ocuparFicha(const Pieza &pieza, const Posicion &pos, Tablero &tablero){
    for(unsigned int i = 0; i < pieza.second.size(); i++){
        for(unsigned int j = 0; j < pieza.second[0].size(); j++){
            tablero[pos.first + i][pos.second + j].second = true;
        }
    }
}
