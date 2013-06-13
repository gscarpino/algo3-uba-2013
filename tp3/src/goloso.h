#ifndef GOLOSO_H_INCLUDED
#define GOLOSO_H_INCLUDED



#include <iostream>
#include <cstdlib>

#include "Grafo.h"

using namespace std;


vector<unsigned int> maximoImpactoGoloso(const Grafo &G, const Grafo &H);
unsigned int calcularImpactoGoloso(const Grafo &H, const vector<int> &coloreo);
bool coloreoLegal(const Grafo &G, const vector<int> &coloreo);
bool esLegalGoloso(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const int color);
unsigned int siguienteModificable(const Grafo &G, const Grafo &H, const vector<bool> &modificados);

void imprimirPosibles(vector< pair<unsigned int, unsigned int > > &posibles);

#endif // GOLOSO_H_INCLUDED
