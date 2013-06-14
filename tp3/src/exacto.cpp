#include "exacto.h"

unsigned long long int contador = 0;

vector<unsigned int> maximoImpactoExacto(const Grafo &G, const Grafo &H){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;

    vector<int> coloreo(G.cantNodos(),-1);
    vector<unsigned int> colores(G.gradoMaximo()+1);

    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++){
        colores[i] = i+1;
    }


    unsigned int visitados = 0;
    RecursiveColorAssignment(0,G,H,coloreo,colores,visitados,res);

    return res;
}

void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G,const Grafo &H, const vector<int> &coloreo, const vector<unsigned int> &colores, const unsigned int visitados, vector< unsigned int> &res){
    for(unsigned int c = 0; c < colores.size(); c++){
        if(G.colorLegalDeNodo(nodo,coloreo,colores[c])){
            vector<int> nuevoColoreo(coloreo);
            nuevoColoreo[nodo] = colores[c];
            if((visitados + 1) >= G.cantNodos()){
                unsigned int temp;
                temp = H.impacto(nuevoColoreo);
                if(temp > res[0]){
                    res[0] = temp;
                    for(unsigned int k = 0; k < nuevoColoreo.size(); k++){
                        res[k + 1] = nuevoColoreo[k];
                    }
                }
//                if(contador == 100000)  cout << ++contador << endl;
            }
            else{
                RecursiveColorAssignment((nodo + 1)%G.cantNodos(),G,H,nuevoColoreo,colores,visitados + 1,res);
            }
        }
    }
}

void mostrarColoreo(const vector<int> &coloreo){
    for(unsigned int i = 0; i < coloreo.size(); i++){
        cout << " " << coloreo[i];
    }
    cout << endl;
}
