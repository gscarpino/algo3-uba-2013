#ifndef LOCAL_H
#define LOCAL_H

#include "goloso.h"


vector<unsigned int> maximoImpactoLocal(const Grafo &G, const Grafo &H, double porcentaje);
vector<unsigned int> maximoImpactoLocal(const Grafo &G, const Grafo &H, const vector<unsigned int> &solGolosa);

#endif // LOCAL_H
