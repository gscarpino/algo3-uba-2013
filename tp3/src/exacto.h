#ifndef EXACTO_H_INCLUDED
#define EXACTO_H_INCLUDED


#include <iostream>
#include <cstdlib>

#include "Grafo.h"

using namespace std;

unsigned int maximoImpactoExacto(const Grafo &grafoG, const Grafo &grafoH);
void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const vector<unsigned int> &colores,const unsigned int visitados, vector<vector<int> > &conjColoreos);
bool esLegal(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const int color );
unsigned int calcularImpacto(const Grafo &H, const vector<int> coloreo);

#endif // EXACTO_H_INCLUDED