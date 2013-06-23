#ifndef EXACTO_H_INCLUDED
#define EXACTO_H_INCLUDED


#include <iostream>
#include <cstdlib>

#include "Grafo.h"

using namespace std;

vector<unsigned int> maximoImpactoExacto(const Grafo &G, const Grafo &H);
vector<unsigned int> maximoImpactoExacto2(const Grafo &G, const Grafo &H);
void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G,const Grafo &H, const vector<unsigned int> &coloreo, const vector<unsigned int> &colores, const unsigned int visitados, vector< unsigned int> &res);
unsigned int calcLimiteImpacto(const Grafo &G, const Grafo &H);
void mostrarColoreo(const vector<unsigned int> &coloreo);

bool generarColoreo(vector<unsigned int> &colores, const Grafo &G, const Grafo &H, vector<unsigned int> &coloreo, unsigned int limite, vector<unsigned int> &solucion);
bool siguienteColoreo(vector<unsigned int> &coloreo, unsigned int nodos, unsigned int colores, unsigned int indice);
void permutacionesDelColoreo(unsigned int nodo, vector<unsigned> &colores, const Grafo &G, const Grafo &H, vector<unsigned int> &solucion, unsigned int limite, vector<unsigned int> coloreo);
bool yaPintadoDeEseColor(unsigned int color, const vector<unsigned int> &colores, unsigned int delimitador);
#endif // EXACTO_H_INCLUDED
