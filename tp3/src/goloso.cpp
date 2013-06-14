#include "goloso.h"


vector<unsigned int> maximoImpactoGoloso(const Grafo &G, const Grafo &H){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;

    vector<int> coloreo(G.cantNodos(),1);
    vector<unsigned int> colores(G.gradoMaximo()+1);

    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++){
        colores[i] = i+1;
    }

    vector<bool> modificados(H.cantNodos(),false);
    unsigned int nodo;
    while(!G.coloreoLegal(coloreo)){
        nodo = siguienteModificable(H,coloreo,modificados);
        for(unsigned int c = 0; c < colores.size(); c++){
            if(G.colorLegalDeNodo(nodo,coloreo,colores[c])){
                coloreo[nodo] = colores[c];
                break;
            }
        }
        modificados[nodo] = true;
    }

    res[0] = H.impacto(coloreo);
    return res;
}

unsigned int siguienteModificable(const Grafo &H, const vector<int> &coloreo, const vector<bool> &modificados){
    vector< pair<unsigned int, unsigned int > > posibles;
    for(unsigned int i = 0; i < H.cantNodos(); i++){
        if(!modificados[i]){
            posibles.push_back(make_pair(impactoNodo(i,H,coloreo),i));
        }
    }

//    sort(posibles.begin(),posibles.end(),cmpSiguiente);
    sort(posibles.begin(),posibles.end());

    return posibles[0].second;
//    return posibles[posibles.size()-1].second;
}

//bool cmpSiguiente(const pair<unsigned int, unsigned int > &a, const pair<unsigned int, unsigned int > &b) const{
//    if(a.first < b.first){
//        return true;
//    }
//    else if(a.first > b.first){
//        return false;
//    }
//    else{
//
//    }
//}

unsigned int impactoNodo(unsigned int nodo, const Grafo &H, const vector<int> &coloreo){
    unsigned int res = 0;
    vector<unsigned int> vecinos(H.vecinosDe(nodo));
    for(unsigned int i = 0; i < vecinos.size(); i++){
        if(coloreo[nodo] == coloreo[vecinos[i]]){
            res++;
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
