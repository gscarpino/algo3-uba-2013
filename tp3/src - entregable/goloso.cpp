#include "goloso.h"


vector<unsigned int> maximoImpactoGoloso(const Grafo &G, const Grafo &H, double porcentaje)
{
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;

    vector<unsigned int> coloreo(G.cantNodos(),1);
    vector<unsigned int> colores(G.gradoMaximo()+1);

    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++)
    {
        colores[i] = i+1;
    }

    vector<bool> modificados(H.cantNodos(),false);
    unsigned int nodo;
    while(!G.coloreoLegal(coloreo))
    {
        nodo = siguienteModificable(G,H,coloreo,modificados,porcentaje);
        for(unsigned int c = 0; c < colores.size(); c++)
        {
            if(G.colorLegalDeNodo(nodo,coloreo,colores[c]))
            {
                coloreo[nodo] = colores[c];
                break;
            }
        }
        modificados[nodo] = true;
    }

    res[0] = H.impacto(coloreo);
    for(unsigned int k = 0; k < coloreo.size(); k++)
    {
        res[k + 1] = coloreo[k];
    }
    return res;
}

unsigned int siguienteModificable(const Grafo &G, const Grafo &H, const vector<unsigned int> &coloreo, const vector<bool> &modificados, double porcentaje)
{
    vector< pair<unsigned int, unsigned int > > posibles;
    for(unsigned int i = 0; i < H.cantNodos(); i++)
    {
        if(!modificados[i] && (H.vecinosDe(i).size() > 0))
        {
            posibles.push_back(make_pair(impactoNodo(i,H,coloreo),i));
        }
    }
    if(posibles.size() == 0)
    {
        for(unsigned int i = 0; i < H.cantNodos(); i++)
        {
            if(!modificados[i])
            {
                posibles.push_back(make_pair(impactoNodo(i,H,coloreo),i));
            }
        }
    }

//    imprimirPosibles(posibles);
    sort(posibles.begin(),posibles.end());
//    imprimirPosibles(posibles);
    for(unsigned int i = 0; i < posibles.size()-1; i++)
    {
        for(unsigned int j = i + 1; j < posibles.size(); j++)
        {
            if(posibles[i].first == posibles[j].first)
            {
                if(G.gradoDe(posibles[i].second) < G.gradoDe(posibles[j].second))
                {
                    swap(posibles[i],posibles[j]);
                }
                else if(G.gradoDe(posibles[i].second) == G.gradoDe(posibles[j].second))
                {
                    if(H.gradoDe(posibles[j].second) < H.gradoDe(posibles[i].second))
                    {
                        swap(posibles[i],posibles[j]);
                    }
                }
            }
        }
    }
//    imprimirPosibles(posibles);
//    exit(0);

    unsigned int res = 0;

    res = rand()%((unsigned int)(posibles.size()*porcentaje) + 1);
    if(res >= posibles.size())
    {
        res = 0;
    }
    return posibles[res].second;
//    return posibles[0].second;
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

unsigned int impactoNodo(unsigned int nodo, const Grafo &H, const vector<unsigned int> &coloreo)
{
    unsigned int res = 0;
    vector<unsigned int> vecinos(H.vecinosDe(nodo));
    for(unsigned int i = 0; i < vecinos.size(); i++)
    {
        if(coloreo[nodo] == coloreo[vecinos[i]])
        {
            res++;
        }
    }
    return res;
}


void imprimirPosibles(vector< pair<unsigned int, unsigned int > > &posibles)
{
    for(unsigned int i = 0; i < posibles.size(); i++)
    {
        cout << " (" << posibles[i].first << "," << posibles[i].second << ") " << endl;
    }
    cout << endl;
}