#ifndef EXACTO_H_INCLUDED
#define EXACTO_H_INCLUDED


#include <iostream>
#include <cstdlib>

#include "Grafo.h"

using namespace std;

vector<unsigned int> maximoImpactoExacto(const Grafo &G, const Grafo &H);
//void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G,const Grafo &H, const vector<int> &coloreo, const vector<unsigned int> &colores, const unsigned int visitados, vector< unsigned int> &res);
unsigned int calcLimiteImpacto(const Grafo &G, const Grafo &H);
void generarColoreosYCalcImpacto(unsigned int nodo, vector<unsigned int> &colores, const Grafo &G, const Grafo &H, const unsigned limite, const vector<unsigned int> &coloreo,unsigned int visitados, vector<unsigned int> &solucion);
void mostrarColoreo(const vector<unsigned int> &coloreo);
#endif // EXACTO_H_INCLUDED
