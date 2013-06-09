#include "exacto.h"


void maximoImpactoExacto(const Grafo &grafoG, const Grafo &grafoH){
    Grafo G(grafoG);
    Grafo H(grafoH);

    //
    vector<int> coloreo(grafoG.cantNodos());
    vector<unsigned int> colores(grafoG.cantNodos());


    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++){
        colores[i] = i;
        coloreo[i] = -1;
    }

    for(unsigned int n = 0; n < G.cantNodos(); n++){
        RecursiveColorAssignment(n,G,coloreo,colores);
    }

}

void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const vector<unsigned int> &colores){
    for(unsigned int c = 0; c < colores.size(); c++){

        vector<int> nuevoColoreo(coloreo);
        if(esLegal(nodo,G,nuevoColoreo,c)){
            nuevoColoreo[nodo] = c;
        }
        if(nodo == (G.cantNodos() - 1)){
            calcularImpacto();
        }
        else{
            RecursiveColorAssignment(nodo+1,G,nuevoColoreo,colores);
        }
    }

}

bool esLegal(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const unsigned int color ){
    bool res = true;

    return res;
}

void calcularImpacto(){

}
