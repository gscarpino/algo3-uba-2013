#include "exacto.h"

unsigned long long int contador = 0;

bool encontrado = false;
bool mejora = false;
unsigned int maxImpactoPosible = 0;

vector<unsigned int> maximoImpactoExacto(const Grafo &G, const Grafo &H){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;
    encontrado = false;

    vector<unsigned int> coloreo(G.cantNodos());

    maxImpactoPosible = calcLimiteImpacto(G,H);
//
//    coloreo[0] = 1;
//    coloreo[1] = 1;
//    coloreo[2] = 1;
//    coloreo[3] = 3;
//    coloreo[4] = 2;
//    coloreo[5] = 2;
//    coloreo[6] = 2;
//    coloreo[7] = 3;
//    coloreo[8] = 1;
//    coloreo[9] = 1;
//    coloreo[10] = 1;
//    coloreo[11] = 2;
//
//    cout << "Testing " << H.impacto(coloreo) << endl;
//    cout << "Legal: " << G.coloreoLegal(coloreo) << endl;
//    cout << "Impacto max posible: " << calcLimiteImpacto(G,H) << endl;
//    exit(0);
    for(unsigned int cantColores = 1; cantColores <= G.cantNodos(); cantColores++){
        cout << "Colores: " << cantColores << endl;
        vector<unsigned int> colores(cantColores);

        for(unsigned int c = 0; c < cantColores; c++){
            colores[c] = c + 1;
        }

        for(unsigned int i = 0; i < coloreo.size(); i++){
            if(i < cantColores){
                coloreo[i] = colores[i];
            }
            else{
                coloreo[i] = 1;
            }
        }
        coloreo[coloreo.size() - 1] = 0;

        if(cantColores < G.cantNodos()){
//            generarColoreosYCalcImpacto(cantColores,colores,G,H,maxImpactoPosible,coloreo,cantColores,res);
            mejora = false;
            while(generarColoreo(colores,G,H,coloreo,maxImpactoPosible,res));
            cout << "Por ahora: " << res[0] << endl;
            if(!mejora && res[0] > 0){
                break;
            }
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
            mostrarColoreo(coloreo);
            system("pause");
        }
        if(encontrado){
            break;
        }
    }

    return res;
}

bool generarColoreo(vector<unsigned int> &colores, const Grafo &G, const Grafo &H, vector<unsigned int> &coloreo, unsigned int limite, vector<unsigned int> &solucion){
    bool res = true;
    res = siguienteColoreo(coloreo,G.cantNodos(),colores.size(),coloreo.size()-1);
    if(res){
        vector<unsigned int> coloreoSinIniciar(coloreo.size(),0);
        permutacionesDelColoreo(0,coloreo,G,H,solucion,limite,coloreoSinIniciar);
//        sort(coloreo.begin(),coloreo.end());
//        do{
//            if(G.coloreoLegal(coloreo)){
//                unsigned int temp;
//                temp = H.impacto(coloreo);
//                if(temp > solucion[0]){
//                    solucion[0] = temp;
//                    for(unsigned int k = 0; k < coloreo.size(); k++){
//                        solucion[k + 1] = coloreo[k];
//                    }
//                    if(solucion[0] == limite) encontrado = true;
//                }
//                if(temp == solucion[0]) mejora = true;
//            }
//        }while(next_permutation(coloreo.begin(),coloreo.end()) && !encontrado);
    }
    return res;
}

bool siguienteColoreo(vector<unsigned int> &coloreo, unsigned int nodos, unsigned int colores, unsigned int indice){
    unsigned int inicio = colores;
    coloreo[indice]++;
    if(coloreo[indice] > colores){
        if(inicio == indice){
            return false;
        }
        else{
            if(siguienteColoreo(coloreo,nodos,colores,indice - 1)){
                coloreo[indice] = coloreo[indice - 1];
            }
            else{
                return false;
            }
        }
    }
    return true;
}

void permutacionesDelColoreo(unsigned int nodo, vector<unsigned> &colores, const Grafo &G, const Grafo &H, vector<unsigned int> &solucion, unsigned int limite, vector<unsigned int> coloreo){
    if(!encontrado){
        if((nodo + 1) >= G.cantNodos()){
            unsigned int temp;
            temp = H.impacto(coloreo);
            if(temp > solucion[0]){
                solucion[0] = temp;
                for(unsigned int k = 0; k < coloreo.size(); k++){
                    solucion[k + 1] = coloreo[k];
                }
            }
            if(solucion[0] == limite) encontrado = true;
        }
        else{
            for(unsigned int c = 0; c < colores.size(); c++){
                if(G.colorLegalDeNodo(nodo,coloreo,coloreo[c])){
                    vector<unsigned int> nuevoColoreo(coloreo);
                    vector<unsigned int> nuevoColores(colores);
                    nuevoColoreo[nodo] = colores[c];
                    nuevoColores.erase(nuevoColores.begin() + c);
                    permutacionesDelColoreo(nodo + 1,nuevoColores,G,H,solucion,limite,nuevoColoreo);
                }
            }
        }
    }

}


void generarColoreosYCalcImpacto(unsigned int nodo, vector<unsigned int> &colores, const Grafo &G, const Grafo &H, const unsigned limite, const vector<unsigned int> &coloreo, unsigned int visitados, vector<unsigned int> &solucion){
    if(!encontrado){
        for(unsigned int c = 0; c < colores.size(); c++){
//            if(G.colorLegalDeNodo(nodo,coloreo,colores[c])){
                vector<unsigned int> nuevoColoreo(coloreo);
                nuevoColoreo[nodo] = colores[c];
                if((visitados + 1) == G.cantNodos()){
                    //Permutar y probar
//                    cout << "Nuevo set: " << endl;
//                    mostrarColoreo(nuevoColoreo);
//                    sort(nuevoColoreo.begin(),nuevoColoreo.end());
//                    do{
//                        if(G.coloreoLegal(nuevoColoreo)){
                            mostrarColoreo(nuevoColoreo);
                            system("pause");
                            unsigned int temp;
                            temp = H.impacto(nuevoColoreo);
                            if(temp > solucion[0]){
                                solucion[0] = temp;
                                for(unsigned int k = 0; k < nuevoColoreo.size(); k++){
                                    solucion[k + 1] = nuevoColoreo[k];
                                }
//                                if(solucion[0] == limite) encontrado = true;
                            }
//                        }
//                    }while(next_permutation(nuevoColoreo.begin(),nuevoColoreo.begin() + colores.size()) && !encontrado);
//                    }while(next_permutation(nuevoColoreo.begin(),nuevoColoreo.end()) && !encontrado);
                }
                else{
                    generarColoreosYCalcImpacto((nodo + 1)%G.cantNodos(),colores,G,H,limite,nuevoColoreo,visitados + 1,solucion);
                }
//            }
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
