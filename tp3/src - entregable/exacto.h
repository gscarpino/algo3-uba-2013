#ifndef EXACTO_H_INCLUDED
#define EXACTO_H_INCLUDED


#include <iostream>
#include <cstdlib>

#include "Grafo.h"

using namespace std;

vector<unsigned int> maximoImpactoExacto(const Grafo &G, const Grafo &H);
void colorear(unsigned int nodo, const Grafo &G, const Grafo &H, vector<unsigned int> &coloreo,vector<unsigned int> &solucion);
#endif // EXACTO_H_INCLUDED
