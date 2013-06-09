#ifndef EXACTO_H_INCLUDED
#define EXACTO_H_INCLUDED


#include <iostream>
#include <cstdlib>

#include "Grafo.h"

using namespace std;

void maximoImpactoExacto(const Grafo &grafoG, const Grafo &grafoH);
void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const vector<unsigned int> &colores);
bool esLegal(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const unsigned int color );
void calcularImpacto();

#endif // EXACTO_H_INCLUDED
