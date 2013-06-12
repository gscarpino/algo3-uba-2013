#include "goloso.h"


vector<unsigned int> maximoImpactoGoloso(const Grafo &grafoG, const Grafo &grafoH){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;

    vector<int> coloreo(G.cantNodos(),-1);
    vector<unsigned int> colores(G.gradoMaximo());

    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++){
        colores[i] = i+1;
    }

    for(unsigned int i = 0; i < H.gr)

}
