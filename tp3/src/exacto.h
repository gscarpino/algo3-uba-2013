#ifndef EXACTO_H_INCLUDED
#define EXACTO_H_INCLUDED


#include <iostream>
#include <cstdlib>

#include "Grafo.h"

using namespace std;

vector<unsigned int> maximoImpactoExacto(const Grafo &grafoG, const Grafo &grafoH);
void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G,const Grafo &H, const vector<int> &coloreo, const vector<unsigned int> &colores, const unsigned int visitados, vector< unsigned int> &res);
bool esLegal(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const int color );
unsigned int calcularImpacto(const Grafo &H, const vector<int> &coloreo);
void mostrarColoreo(const vector<int> &coloreo);

#endif // EXACTO_H_INCLUDED
