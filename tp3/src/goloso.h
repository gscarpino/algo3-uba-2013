#ifndef GOLOSO_H_INCLUDED
#define GOLOSO_H_INCLUDED



#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Grafo.h"

using namespace std;


vector<unsigned int> maximoImpactoGoloso(const Grafo &G, const Grafo &H, double porcentaje);
unsigned int siguienteModificable(const Grafo &G, const Grafo &H, const vector<int> &coloreo, const vector<bool> &modificados, double porcentaje);
void imprimirPosibles(vector< pair<unsigned int, unsigned int > > &posibles);
unsigned int impactoNodo(unsigned int nodo, const Grafo &H, const vector<int> &coloreo);
#endif // GOLOSO_H_INCLUDED
