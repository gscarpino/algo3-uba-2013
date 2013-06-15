#include "local.h"

vector<unsigned int> maximoImpactoLocal(const Grafo &G, const Grafo &H){
    vector<unsigned int> impactoGoloso(maximoImpactoGoloso(G,H));
    unsigned int impactoParcial = impactoGoloso[0];
    vector<int> coloreo;
//    for(unsigned int i = 0; i < impactoGoloso.size(); i++){
//        cout << impactoGoloso[i] << " ";
//    }
//    cout << endl;
    for(unsigned int i = 1; i < impactoGoloso.size(); i++){
        coloreo.push_back(impactoGoloso[i]);
    }
//
//    for(unsigned int i = 0; i < coloreo.size(); i++){
//        cout << coloreo[i] << " ";
//    }
//    cout << endl;

    unsigned int nuevoImpacto = 0;
    for(unsigned int i = 0; i < H.cantNodos(); i++){
        vector<unsigned int> vecinos(H.vecinosDe(i));
        for(unsigned int n = 0; n < vecinos.size(); n++){
            unsigned int color = coloreo[vecinos[n]];
            if(G.colorLegalDeNodo(i,coloreo,color)){
                vector<int> nuevoColoreo(coloreo);
                nuevoColoreo[i] = color;
                nuevoImpacto = H.impacto(nuevoColoreo);
                if(nuevoImpacto > impactoParcial){
                    coloreo[i] = color;
                    impactoParcial = nuevoImpacto;
                }
            }
        }
    }


    impactoGoloso[0] = impactoParcial;
    for(unsigned int i = 0; i < coloreo.size(); i++){
        impactoGoloso[i+1] = coloreo[i];
    }

    return impactoGoloso;
}


