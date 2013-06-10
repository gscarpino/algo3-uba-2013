#include "exacto.h"


vector<unsigned int> maximoImpactoExacto(const Grafo &grafoG, const Grafo &grafoH){
    vector<unsigned int> res(grafoG.cantNodos() + 1);
    Grafo G(grafoG);
    Grafo H(grafoH);

    vector<int> coloreo(grafoG.cantNodos());
    vector<unsigned int> colores(grafoG.cantNodos());


    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++){
        colores[i] = i;
        coloreo[i] = -1;
    }

    unsigned int visitados = 0;
    vector<vector<int> > conjColoreos;
    RecursiveColorAssignment(0,G,coloreo,colores,visitados,conjColoreos);
    res[0] = 0;
    for(unsigned int i = 0; i < conjColoreos.size(); i++){
        unsigned int temp;
        temp = calcularImpacto(H,conjColoreos[i]);
//        if(temp == 0){
//            mostrarColoreo(conjColoreos[i]);
//        }
        if(temp > res[0]){
            res[0] = temp;
            for(unsigned int c = 0; c < conjColoreos[i].size(); c++){
                res[c + 1] = conjColoreos[i][c];
            }
        }
    }
    return res;
}

void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const vector<unsigned int> &colores, const unsigned int visitados, vector<vector<int> > &conjColoreos){
    for(unsigned int c = 0; c < colores.size(); c++){
        if(esLegal(nodo,G,coloreo,c)){
            vector<int> nuevoColoreo(coloreo);
            nuevoColoreo[nodo] = c;
            if((visitados + 1) >= G.cantNodos()){
                conjColoreos.push_back(nuevoColoreo);
            }
            else{
                RecursiveColorAssignment((nodo + 1)%G.cantNodos(),G,nuevoColoreo,colores,visitados + 1,conjColoreos);
            }
        }
    }
}

bool esLegal(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const int color){
    bool res = true;
    vector<unsigned int> vecinos(G.vecinosDe(nodo));

    for(unsigned int i = 0; i < vecinos.size(); i++){
        if(coloreo[vecinos[i]] == color){
            res = false;
            break;
        }
    }
    return res;
}

unsigned int calcularImpacto(const Grafo &H, const vector<int> &coloreo){
    unsigned int res = 0;
    for(unsigned int i = 0; i < H.cantNodos(); i++){
        vector<unsigned int> vecinos(H.vecinosDe(i));
        for(unsigned int j = 0; j < vecinos.size(); j++){
            if(coloreo[i] == coloreo[vecinos[j]]){
                res++;
            }
        }
    }
    res /=2;
    return res;
}


void mostrarColoreo(const vector<int> &coloreo){
    for(unsigned int i = 0; i < coloreo.size(); i++){
        cout << " " << coloreo[i];
    }
    cout << endl;
}
