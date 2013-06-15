#ifndef GOLOSO_H_INCLUDED
#define GOLOSO_H_INCLUDED



#include <iostream>
#include <cstdlib>

#include "Grafo.h"

using namespace std;


vector<unsigned int> maximoImpactoGoloso(const Grafo &G, const Grafo &H);
unsigned int siguienteModificable(const Grafo &G, const Grafo &H, const vector<int> &coloreo, const vector<bool> &modificados);
void imprimirPosibles(vector< pair<unsigned int, unsigned int > > &posibles);
unsigned int impactoNodo(unsigned int nodo, const Grafo &H, const vector<int> &coloreo);
#endif // GOLOSO_H_INCLUDED
