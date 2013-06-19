#include "exacto.h"

unsigned long long int contador = 0;

bool encontrado = false;
unsigned int maxImpactoPosible = 0;
unsigned int test = 0;

vector<unsigned int> maximoImpactoExacto(const Grafo &G, const Grafo &H){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;
    encontrado = false;

    vector<unsigned int> coloreo(G.cantNodos(),0);

    maxImpactoPosible = calcLimiteImpacto(G,H);
    unsigned int impactoParcial = 0;

    coloreo[0] = 1;
    coloreo[1] = 1;
    coloreo[2] = 1;
    coloreo[3] = 3;
    coloreo[4] = 2;
    coloreo[5] = 2;
    coloreo[6] = 2;
    coloreo[7] = 3;
    coloreo[8] = 1;
    coloreo[9] = 1;
    coloreo[10] = 1;
    coloreo[11] = 2;

    cout << "Testing " << H.impacto(coloreo) << endl;
    cout << "Legal: " << G.coloreoLegal(coloreo) << endl;
//    exit(0);
//    for(unsigned int cantColores = 3; cantColores <= G.cantNodos(); cantColores++){
    for(unsigned int cantColores = 3; cantColores <= 3; cantColores++){
        vector<unsigned int> colores(cantColores);
        for(unsigned int c = 0; c < cantColores; c++){
            colores[c] = c + 1;
        }
        for(unsigned int i = 0; i < cantColores; i++){
            coloreo[i] = colores[i];
        }
        if(cantColores < G.cantNodos()){
            generarColoreosYCalcImpacto(cantColores,colores,G,H,maxImpactoPosible,coloreo,cantColores,res);
        }
        else{
            unsigned int temp;
            temp = H.impacto(coloreo);
            if(temp > res[0]){
                res[0] = temp;
                for(unsigned int k = 0; k < coloreo.size(); k++){
                    res[k + 1] = coloreo[k];
                }
            }
        }
        if(encontrado){
            break;
        }
    }

    return res;
}

void generarColoreosYCalcImpacto(unsigned int nodo, vector<unsigned int> &colores, const Grafo &G, const Grafo &H, const unsigned limite, const vector<unsigned int> &coloreo, unsigned int visitados, vector<unsigned int> &solucion){
    if(!encontrado){
        for(unsigned int c = 0; c < colores.size(); c++){
            if(G.colorLegalDeNodo(nodo,coloreo,colores[c])){
                vector<unsigned int> nuevoColoreo(coloreo);
                nuevoColoreo[nodo] = colores[c];
                if((visitados + 1) == G.cantNodos()){
                    //Permutar y probar
                    do{
                        if(G.coloreoLegal(nuevoColoreo)){
                            mostrarColoreo(nuevoColoreo);
                            unsigned int temp;
                            temp = H.impacto(nuevoColoreo);
                            if(temp == 16){
                                system("pause");
                            }
                            if(temp > solucion[0]){
                                solucion[0] = temp;
                                for(unsigned int k = 0; k < nuevoColoreo.size(); k++){
                                    solucion[k + 1] = nuevoColoreo[k];
                                }
//                                if(solucion[0] == limite) encontrado = true;
                            }
                        }
                    }while(next_permutation(nuevoColoreo.begin(),nuevoColoreo.begin() + colores.size()) && !encontrado);
                }
                else{
                    generarColoreosYCalcImpacto((nodo + 1)%G.cantNodos(),colores,G,H,limite,nuevoColoreo,visitados + 1,solucion);
                }
            }
        }
    }
}
//
//unsigned int calcularImpacto(const vector<unsigned int> coloreo,const Grafo &H,unsigned int limite){
//
//}

//void RecursiveColorAssignment(const unsigned int nodo, const Grafo &G,const Grafo &H, const vector<int> &coloreo, const vector<unsigned int> &colores, const unsigned int visitados, vector< unsigned int> &res){
//    for(unsigned int c = 0; c < colores.size(); c++){
//        if(!encontrado){
//            if(visitados < G.cantNodos() && H.gradoDe(nodo) == 0){
//                RecursiveColorAssignment((nodo + 1)%G.cantNodos(),G,H,coloreo,colores,visitados + 1,res);
//            }
//            else{
//                if(G.colorLegalDeNodo(nodo,coloreo,colores[c])){
//                    vector<int> nuevoColoreo(coloreo);
//                    nuevoColoreo[nodo] = colores[c];
//                    if((visitados + 1) >= G.cantNodos()){
//                        unsigned int temp;
//                        temp = H.impacto(nuevoColoreo);
//                        if(temp > res[0]){
//                            res[0] = temp;
//                            for(unsigned int k = 0; k < nuevoColoreo.size(); k++){
//                                res[k + 1] = nuevoColoreo[k];
//                            }
//                        }
//                        if(res[0] == maxImpactoPosible) encontrado = true;
//    //                    if(contador == 100000)
////                            cout << ++contador << endl;
//                    }
//                    else{
//                        RecursiveColorAssignment((nodo + 1)%G.cantNodos(),G,H,nuevoColoreo,colores,visitados + 1,res);
//                    }
//                }
//            }
//        }
//    }
//}
//
void mostrarColoreo(const vector<unsigned int> &coloreo){
    for(unsigned int i = 0; i < coloreo.size(); i++){
        cout << " " << coloreo[i];
    }
    cout << endl;
}

unsigned int calcLimiteImpacto(const Grafo &G, const Grafo &H){
    unsigned int res = 0;
    for(unsigned int i = 0; i < H.cantNodos(); i++){
        for(unsigned int j = i+1; j < H.cantNodos(); j++){
            if(G.sonVecinos(i,j) && H.sonVecinos(i,j)){
                res++;
            }
        }
        if(H.vecinosDe(i).size() == 1){
            unsigned int nodo = H.vecinosDe(i)[0];
            vector<unsigned int> vecinos(H.vecinosDe(nodo));
            for(unsigned int k = 0; k < vecinos.size(); k++){
                if(G.sonVecinos(i,vecinos[k])){
                    res++;
                }
            }
        }
    }
//    cout << "desc: " << res << " - maxImpPos: " <<  (H.cantAristas() - res) << endl;
    res = H.cantAristas() - res;
    return res;
}
