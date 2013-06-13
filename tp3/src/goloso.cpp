#include "goloso.h"


vector<unsigned int> maximoImpactoGoloso(const Grafo &G, const Grafo &H){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;

    vector<int> coloreo(G.cantNodos(),1);
//    vector<unsigned int> colores(G.gradoMaximo()+1);
    vector<unsigned int> colores(G.gradoMaximo()+1);

    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++){
        colores[i] = i+1;
    }

    vector<bool> modificados(H.cantNodos(),false);
    unsigned int nodo;
    while(!coloreoLegal(G,coloreo)){
        nodo = siguienteModificable(G,H,modificados);
        for(unsigned int c = 0; c < colores.size(); c++){
            if(esLegalGoloso(nodo,G,coloreo,colores[c])){
                coloreo[nodo] = colores[c];
                break;
            }
        }
        modificados[nodo] = true;
    }

    res[0] = calcularImpactoGoloso(H,coloreo);
    return res;
}

unsigned int siguienteModificable(const Grafo &G, const Grafo &H, const vector<bool> &modificados){
    vector< pair<unsigned int, unsigned int > > posibles;
    for(unsigned int i = 0; i < G.cantNodos(); i++){
        if(!modificados[i]){
            posibles.push_back(make_pair(H.vecinosDe(i).size(),i));
//            posibles.push_back(make_pair(G.vecinosDe(i).size(),i));
        }
    }

    sort(posibles.begin(),posibles.end());

//    return posibles[posibles.size()-1].second;
    return posibles[posibles.size()/6].second;
}


unsigned int calcularImpactoGoloso(const Grafo &H, const vector<int> &coloreo){
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

bool esLegalGoloso(const unsigned int nodo, const Grafo &G, const vector<int> &coloreo, const int color){
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

bool coloreoLegal(const Grafo &G, const vector<int> &coloreo){
    bool res = true;
    for(unsigned int i = 0; i < G.cantNodos(); i++){
        vector<unsigned int> vecinos(G.vecinosDe(i));
        for(unsigned int j = 0; j < vecinos.size(); j++){
            if(coloreo[i] == coloreo[vecinos[j]]){
                res = false;
                break;
            }
        }
        if(!res){
            break;
        }
    }
    return res;
}

void imprimirPosibles(vector< pair<unsigned int, unsigned int > > &posibles){
    for(unsigned int i = 0; i < posibles.size();i++){
        cout << " (" << posibles[i].first << "," << posibles[i].second << ") " << endl;
    }
    cout << endl;
}
