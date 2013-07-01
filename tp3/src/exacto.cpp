#include "exacto.h"

vector<unsigned int> maximoImpactoExacto(const Grafo &G, const Grafo &H)
{
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;

    vector<unsigned int> coloreo(G.cantNodos(),0);
    vector<unsigned int> colores(G.cantNodos());

    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++)
    {
        colores[i] = i+1;
    }

    coloreo[0] = 1;
    colorear(1,G,H,coloreo,res);

    return res;
}

void colorear(unsigned int nodo, const Grafo &G, const Grafo &H, vector<unsigned int> &coloreo,vector<unsigned int> &solucion)
{

    if(nodo >= G.cantNodos())
    {
        unsigned int temp;
        temp = H.impacto(coloreo);
        if(temp > solucion[0])
        {
            solucion[0] = temp;
            for(unsigned int k = 0; k < coloreo.size(); k++)
            {
                solucion[k + 1] = coloreo[k];
            }
        }
    }
    else
    {
        unsigned int maxColor = *max_element(coloreo.begin(),coloreo.end());
        for(unsigned int c = 1; c <= (maxColor+1); c++)
        {
            if(G.colorLegalDeNodo(nodo,coloreo,c))
            {
                vector<unsigned int> nuevoColoreo(coloreo);
                nuevoColoreo[nodo] = c;
                colorear(nodo+1,G,H,nuevoColoreo,solucion);
            }
        }
    }

}
