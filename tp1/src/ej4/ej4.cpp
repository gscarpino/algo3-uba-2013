#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "Redefs.h"
#include "Tablero.h"
#include "Pieza.h"

#define TESTING 1


Solucion buscarSol(const Tablero &tablero, vector<Pieza> &piezas);
vector< vector<Pieza> > subConjuntosDeTam(const vector<Pieza> &piezas, int tamanio);
bool esSolucion(const vector<Pieza> &piezas, const Tablero &tablero, Solucion &sol);
bool cubreExactoElTablero(const vector<Pieza> &piezas, const Matriz &tablero,const int dimN, const int dimM);
vector<int> pasarBinario(int n);
bool resolverJuego(vector<Pieza> piezas, Tablero tablero, Solucion &sol);
void descartarPiezas(vector<Pieza> &piezas, const Tablero &tablero);
vector< vector<unsigned int> > powerSet(const vector<Pieza> &piezas);
void powerSetAux(vector<unsigned int> &piezas,vector< vector<unsigned int> >  &res);
void duplicar(vector< vector<unsigned int> >  &res);
void agregarPrimerMitad(unsigned int p, vector< vector<unsigned int> >  &res);
bool cmpSubsPowerSet(const vector<unsigned int> &a, const vector<unsigned int> &b);

vector<Pieza> obtenerPiezas(const Tablero &t, int cant);
void agregarPiezasAlAzar(const Tablero &t, vector<Pieza> &piezas, const unsigned int cant);

int main(int argc, char *argv[]) {

    if(TESTING){
        srand(time(NULL));
        cout << "Generando test azar con solucion" << endl;
        ofstream ftest("testAzarConSol.txt");
        if(ftest.is_open()){
            int repeticiones = 10;
            int maxW=4,maxH=4;
            for(int i = 2; i <= maxW; i = i + 2){
                for(int j = 2; j <= maxH; j = j + 2){
                    for(int r = 0; r < repeticiones; r++){
                        Tablero tab(i,j);
                        vector<Pieza> pie = obtenerPiezas(tab,min(i,j));
                        agregarPiezasAlAzar(tab,pie,4);
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
        ftest << "#";
        ftest.close();
        cout << "Tests creados." << endl;

        cout << "Generando test azar con poca probabilidad de solucion" << endl;

        ftest.open("testAzar.txt");
        if(ftest.is_open()){
            int repeticiones = 100;
            int maxW=5,maxH=5;
            for(int i = 2; i <= maxW; i = i + 2){
                for(int j = 2; j <= maxH; j = j + 2){
                    for(int r = 0; r < repeticiones; r++){
                        Tablero tab(i,j);
                        vector<Pieza> pie;
                        agregarPiezasAlAzar(tab,pie,max(rand() % 30 + 4,10));
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
        cout << "Tests creados." << endl;
        ftest << "#";
        ftest.close();
        return 0;
    }
    if(argc <= 1) {
      cout << "Modo de uso: ej1 archivoEntrada archivoSalida";
      return 0;
    }
    argv[1] = "testAzar.txt";
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
        outputFile  << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}

//Se recorre linealmente de cantidad de subconjuntos de un conjunto si es solucion del problema
Solucion buscarSol(const Tablero &tablero, vector<Pieza> &piezas){
    Solucion res;

    //Primera poda

//    cout << endl << endl << "Piezas antes 1era poda " << piezas.size() << endl;
    descartarPiezas(piezas,tablero);
//    cout << endl << endl << "Piezas despues 1era poda " << piezas.size() << endl;
//    for(int i = 0; i < piezas.size(); i++){
//        cout << endl << "- - -" << endl;
//        piezas[i].imprimir();
//        cout << "- - -" << endl;
//    }

    vector< vector<unsigned int> > subConjuntos;

    subConjuntos = powerSet(piezas);
    sort(subConjuntos.begin(),subConjuntos.end(),cmpSubsPowerSet);
    vector<Pieza> piezasReales;
    for(unsigned int j = 0; j < subConjuntos.size(); j++){
        if(subConjuntos[j].size() > 0){
//            cout << "Probando con " <<  subConjuntos[j].size() << endl;
            for(unsigned int k = 0; k < subConjuntos[j].size(); k++){
                for(unsigned int m = 0; m < piezas.size(); m++){
                    if(piezas[m].getID() == subConjuntos[j][k]){
                        piezasReales.push_back(piezas[m]);
                    }
                }
            }
            if(esSolucion(piezasReales,tablero,res)){
//                cout << "Se encontro sol con " <<  piezasReales.size() << " piezas." << endl;
//                if(piezasReales.size() == 1){
//                    tablero.imprimir();
//                    piezasReales[0].imprimir();
//                }
                break;
            }
            piezasReales.clear();
            subConjuntos[j].clear();
        }
    }
    return res;
}

vector< vector<unsigned int> > powerSet(const vector<Pieza> &piezas){
    vector<unsigned int> copiaPiezas;
    for(unsigned int i = 0; i < piezas.size(); i++){
        copiaPiezas.push_back(piezas[i].getID());
    }
    vector< vector<unsigned int> >  res;
    powerSetAux(copiaPiezas,res);
    return res;
}

void powerSetAux(vector<unsigned int> &piezas,vector< vector<unsigned int> >  &res){
    if(piezas.size() == 0) {
        //Se termina
    }
    else{
        unsigned int p = piezas.back();
        piezas.pop_back();
        duplicar(res);
        agregarPrimerMitad(p,res);
        powerSetAux(piezas,res);
    }
}

void duplicar(vector< vector<unsigned int> >  &res){
    if(res.size() == 0){
        vector<unsigned int> p1,p2;
        res.push_back(p1);
        res.push_back(p2);
    }
    else{
        int tam = res.size();
        for(int i = 0; i < tam; i++){
            try{
                res.push_back(res[i]);
            }
            catch (bad_alloc&){
                cout << "Memoria insuficiente" << endl;
                exit(1);
            }
        }
    }
}

void agregarPrimerMitad(unsigned int p, vector< vector<unsigned int> >  &res){
    for(unsigned int i = 0; i < (res.size() / 2); i++){
        res[i].push_back(p);
    }
}


bool cmpSubsPowerSet(const vector<unsigned int> &a, const vector<unsigned int> &b){
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


vector<Pieza> obtenerPiezas(const Tablero &t, int cant){
    vector<Pieza> res;
    int cant_x = cant;
    int cant_y = cant;

    while(t.getRows() % cant_x){
        cant_x--;
    }

    int corte_rows = t.getRows() / cant_x;


    while(t.getCols() % cant_y){
        cant_y--;
    }

    int corte_cols = t.getCols() / cant_y;


    for(int i = 0; i < cant_x * cant_y; i++){
        Vec cols(corte_cols);
        Matriz mp;
        for(int j = 0; j < corte_rows; j++){
            mp.push_back(cols);
        }
        Pieza p(mp,i);
        res.push_back(p);
    }


    //Copia de color
    int id,x,y;
    for(unsigned int i = 0; i < t.getRows(); i++){
        for(unsigned int j = 0; j < t.getCols(); j++){
            id = (i / corte_rows) * cant_y + (j / corte_cols);
            x = (i % corte_rows);
            y = (j % corte_cols);
            res[id].setColor(x,y,t.getColor(i,j));
        }
    }

//    for(unsigned int i = 0; i < res.size(); i++){
//        res[i].imprimir();
//    }
    return res;
}

void agregarPiezasAlAzar(const Tablero &t, vector<Pieza> &piezas, const unsigned int cant){
    srand(time(NULL));
    int x,y, minId = piezas.size();
    for(unsigned int i = 0; i < cant; i++){
        x = rand() % t.getRows() + 1;
        y = rand() % t.getCols() + 1;
        Vec cols(y);
        Matriz mp;
        for(int j = 0; j < x; j++){
            for(int k = 0; k < y; k++){
                cols[k] = rand() % 2;
            }
            mp.push_back(cols);
        }
        Pieza p(mp,minId + i);
        piezas.push_back(p);
//        p.imprimir();
    }
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

