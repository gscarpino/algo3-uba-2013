#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "Redefs.h"
#include "Tablero.h"
#include "Pieza.h"

#define TESTING 0


Solucion buscarSol(const Tablero &tablero, vector<Pieza> &piezas);
vector< vector<Pieza> > subConjuntosDeTam(const vector<Pieza> &piezas, int tamanio);
bool esSolucion(const vector<Pieza> &piezas, const Tablero &tablero, Solucion &sol);
bool cubreExactoElTablero(const vector<Pieza> &piezas, const Matriz &tablero,const int dimN, const int dimM);
vector<int> pasarBinario(int n);
bool resolverJuego(vector<Pieza> piezas, Tablero tablero, Solucion &sol);
void descartarPiezas(vector<Pieza> &piezas, const Tablero &tablero);
vector< vector<Pieza> > powerSet(const vector<Pieza> &piezas);
void powerSetAux(vector<Pieza> &piezas,vector< vector<Pieza> >  &res);
void duplicar(vector< vector<Pieza> >  &res);
void agregarPrimerMitad(Pieza p, vector< vector<Pieza> >  &res);
bool cmpSubsPowerSet(const vector<Pieza> &a, const vector<Pieza> &b);

Tablero crearTableroAzar(const int w, const int h);
vector<Pieza> obtenerPiezasAlAzar(const Tablero &t);
void agregarPiezasAlAzar(vector<Pieza> &piezas);

int main(int argc, char *argv[]) {

    if(TESTING){
        ofstream ftest("testingAzar.txt");
        if(ftest.is_open()){
            int repeticiones = 10;
            int maxW=5,maxH=5;
            for(int i = 1; i < maxW; i++){
                for(int j = 1; j < maxH; j++){
                    for(int r = 0; r < repeticiones; r++){
                        Tablero tab = crearTableroAzar(i,j);
                        vector<Pieza> pie = obtenerPiezasAlAzar(tab);
                        agregarPiezasAlAzar(pie);
                        ftest << i << " " << j << " " << pie.size() <<  endl;
                        for(unsigned int r = 0; r < tab.getRows(); r++){
                            ftest << tab.getColor(r,0);
                            for(unsigned int f = 1; f < tab.getCols(); f++){
                                ftest << " " << tab.getColor(r,f);
                            }
                            ftest << endl;
                        }
                        for(unsigned int p = 0; p < pie.size(); p++){
                            ftest << pie[p].getRows() << " " << pie[p].getCols() << endl;
                            for(unsigned int r = 0; r < pie[p].getRows(); r++){
                                ftest << pie[p].getColor(r,0);
                                for(unsigned int f = 1; f < pie[p].getCols(); f++){
                                    ftest << " " << pie[p].getColor(r,f);
                                }
                                ftest << endl;
                            }
                        }
                    }
                }
            }
        }
    }

    if(argc <= 1) {
      cout << "Modo de uso: ej1 archivoEntrada archivoSalida";
      return 0;
    }
//    argv[1] = "input.txt";
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
                break;
//                return 1;
            }
            temp++;
        }
        //Se va a ir cargando la matriz del tablero
        Vec fila(dimM);
        Matriz tableroTemp;
        for(int i = 0; i < dimN; i++){
            getline(inputFile, linea);
            istringstream sLinea2(linea);
            for(int j = 0; j < dimM; j++){
                sLinea2 >> n;
                fila[j] = n;
            }
            tableroTemp.push_back(fila);
        }

        //Se va a ir cargando las piezas
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


        Tablero tablero(tableroTemp,dimN,dimM);
//        testTablero.imprimir();
//        testTablero.imprimirConFichas();
//
//        cout << endl << endl << "Piezas: " << endl;
//        for(int i = 0; i < cantPiezas; i++){
//            cout << endl << "- - -" << endl;
//            piezas[i].imprimir();
//            cout << "- - -" << endl;
//        }


        Solucion solucion = buscarSol(tablero,piezas);
//        cout << "Tamanio de la solucion final: " << solucion.size() << endl;
        cout << "[";
        for(unsigned int i = 0; i < solucion.size(); i++){
            solucion[i].imprimir();
        }
        cout << "]" << endl;

        outputFile << solucion.size();
        for(unsigned int i = 0; i < solucion.size(); i++){
            outputFile << endl;
            outputFile << solucion[i];
        }
    }

    inputFile.close();
    outputFile.close();
    return 0;
}

//Se recorre linealmente de cantidad de subconjuntos de un conjunto si es solucion del problema
Solucion buscarSol(const Tablero &tablero, vector<Pieza> &piezas){
    Solucion res;

    //Primera poda
    descartarPiezas(piezas,tablero);
//    cout << endl << endl << "Piezas: " << endl;
//    for(int i = 0; i < piezas.size(); i++){
//        cout << endl << "- - -" << endl;
//        piezas[i].imprimir();
//        cout << "- - -" << endl;
//    }

    vector< vector<Pieza> > subConjuntos;

    subConjuntos = powerSet(piezas);
    sort(subConjuntos.begin(),subConjuntos.end(),cmpSubsPowerSet);
    for(unsigned int j = 0; j < subConjuntos.size(); j++){
        if(subConjuntos[j].size() > 0){
            cout << "Probando con " <<  subConjuntos[j].size() << endl;
            if(esSolucion(subConjuntos[j],tablero,res)){
                cout << "Se encontro sol con " <<  subConjuntos[j].size() << " piezas." << endl;
                break;
            }
        }
    }
    return res;
}

vector< vector<Pieza> > powerSet(const vector<Pieza> &piezas){
    vector<Pieza> copiaPiezas = piezas;
    vector< vector<Pieza> >  res;
    powerSetAux(copiaPiezas,res);
    return res;
}

void powerSetAux(vector<Pieza> &piezas,vector< vector<Pieza> >  &res){
    if(piezas.size() == 0) {
        //Se termina
    }
    else{
        Pieza p = piezas.back();
        piezas.pop_back();
        duplicar(res);
        agregarPrimerMitad(p,res);
        powerSetAux(piezas,res);
    }
}

void duplicar(vector< vector<Pieza> >  &res){
    if(res.size() == 0){
        vector<Pieza> p1,p2;
        res.push_back(p1);
        res.push_back(p2);
    }
    else{
        int tam = res.size();
        for(int i = 0; i < tam; i++){
            res.push_back(res[i]);
        }
    }
}

void agregarPrimerMitad(Pieza p, vector< vector<Pieza> >  &res){
    for(int i = 0; i < (res.size() / 2); i++){
        res[i].push_back(p);
    }
}


bool cmpSubsPowerSet(const vector<Pieza> &a, const vector<Pieza> &b){
    return a.size() < b.size();
}

//Determina si un conjunto dado de piezas es solucion al problema
bool esSolucion(const vector<Pieza> &piezas, const Tablero &tablero, Solucion &sol){
    bool res = false;

    //Poda de que para que sea una solucion optima tiene que cubrir todo el tablero en superficie, ni mas ni menos
    if(tablero.cubreTodo(piezas)){
        res = resolverJuego(piezas,tablero,sol);
    }
    return res;
}


bool resolverJuego(vector<Pieza> piezas, Tablero tablero, Solucion &sol){
    bool res= false;
    if(piezas.size() == 0){
        res = tablero.completo();
        if(res){
            sol = tablero.obtenerPiezas();
        }
    }
    else{
        Pieza sigPieza(piezas.back());
        piezas.pop_back();

        vector<Posicion> posiciones;

        posiciones = tablero.posiblesPosiciones(sigPieza);
        for(unsigned int i = 0; i < posiciones.size(); i++){
            Tablero nuevoTablero(tablero);
            nuevoTablero.ubicarFicha(sigPieza,0,posiciones[i]);
            res = resolverJuego(piezas,nuevoTablero,sol);
            if(res) break;
        }

        //Poda de cuando rotar una pieza es igual que no rotarla
        Pieza sigPieza2 = sigPieza.rotar();
        if(sigPieza != sigPieza2 && !res){
            Pieza sigPieza3 = sigPieza2.rotar();
            Pieza sigPieza4 = sigPieza3.rotar();
            posiciones = tablero.posiblesPosiciones(sigPieza2);
            for(unsigned int i = 0; i < posiciones.size(); i++){
                Tablero nuevoTablero(tablero);
                nuevoTablero.ubicarFicha(sigPieza2,1,posiciones[i]);
                res = resolverJuego(piezas,nuevoTablero,sol);
                if(res) break;
            }
            if(!res){
                posiciones = tablero.posiblesPosiciones(sigPieza3);
                for(unsigned int i = 0; i < posiciones.size(); i++){
                    Tablero nuevoTablero(tablero);
                    nuevoTablero.ubicarFicha(sigPieza3,2,posiciones[i]);
                    res = resolverJuego(piezas,nuevoTablero,sol);
                    if(res) break;
                }
            }
            if(!res){
                posiciones = tablero.posiblesPosiciones(sigPieza4);
                for(unsigned int i = 0; i < posiciones.size(); i++){
                    Tablero nuevoTablero(tablero);
                    nuevoTablero.ubicarFicha(sigPieza4,3,posiciones[i]);
                    res = resolverJuego(piezas,nuevoTablero,sol);
                    if(res) break;
                }
            }

        }

    }
    return res;
}




Tablero crearTableroAzar(const int w, const int h){
    Tablero res(w,h);
    return res;
}

vector<Pieza> obtenerPiezasAlAzar(const Tablero &t){
    vector<Pieza> res;
    return res;
}

void agregarPiezasAlAzar(vector<Pieza> &piezas){

}

void descartarPiezas(vector<Pieza> &piezas, const Tablero &tablero){
    vector<unsigned int> IDborrables;

    for(unsigned int i = 0; i < piezas.size(); i++){
        if(!tablero.cabe(piezas[i])){
            IDborrables.push_back(piezas[i].getID());
        }
    }

    for(unsigned int i = 0; i < IDborrables.size(); i++){
        for(unsigned int j = 0; j < piezas.size(); j++){
            if(piezas[j].getID() == IDborrables[i]){
                piezas.erase(piezas.begin() + j);
                break;
            }
        }
    }
}
