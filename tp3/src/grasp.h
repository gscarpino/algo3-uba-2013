#ifndef GRASP_H
#define GRASP_H


#include <iostream>
#include <cstdlib>

#include "Grafo.h"
#include "goloso.h"
#include "local.h"

using namespace std;

vector<unsigned int> maximoImpactoGrasp(const Grafo &G, const Grafo &H, double porcentaje);
void imprimirVector(const vector<unsigned int> &v);
#endif // GRASP_H
