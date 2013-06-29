#include "exacto.h"

unsigned long long int contador = 0;

bool encontrado = false;
bool mejora = false;
unsigned int maxImpactoPosible = 0;
bool huboColoreoLegal = false;

vector<unsigned int> maximoImpactoExacto(const Grafo &G, const Grafo &H){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;
    encontrado = false;

    vector<unsigned int> coloreo(G.cantNodos());

    maxImpactoPosible = calcLimiteImpacto(G,H);

    for(unsigned int cantColores = 1; cantColores <= G.cantNodos(); cantColores++){
//        cout << "Colores: " << cantColores << endl;
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
            mejora = false;
            huboColoreoLegal = false;
            while(generarColoreo(colores,G,H,coloreo,maxImpactoPosible,res));
//            cout << "Por ahora: " << res[0] << endl;
//            if(!mejora && res[0] > 0){
//                break;
//            }
//            cout << "Contador: " << contador << endl;
            contador = 0;
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

bool generarColoreo(vector<unsigned int> &colores, const Grafo &G, const Grafo &H, vector<unsigned int> &coloreo, unsigned int limite, vector<unsigned int> &solucion){
    bool res = true;
    res = siguienteColoreo(coloreo,G.cantNodos(),colores.size(),coloreo.size()-1);
    if(res){
        huboColoreoLegal = true;
        vector<unsigned int> coloreoSinIniciar(coloreo.size(),0);
        permutacionesDelColoreo(0,coloreo,G,H,solucion,limite,coloreoSinIniciar);
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
        if(nodo >= G.cantNodos()){
            unsigned int temp;
            temp = H.impacto(coloreo);
            mejora = mejora || (temp > solucion[0]);
            if(temp > solucion[0]){
                solucion[0] = temp;
                for(unsigned int k = 0; k < coloreo.size(); k++){
                    solucion[k + 1] = coloreo[k];
                }
            }
//            if(solucion[0] == limite) encontrado = true;
            contador++;
        }
        else{
            for(unsigned int c = 0; c < colores.size(); c++){
                if(!yaPintadoDeEseColor(colores[c],colores,c)){
                    if(G.colorLegalDeNodo(nodo,coloreo,colores[c])){
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
}

bool yaPintadoDeEseColor(unsigned int color, const vector<unsigned int> &colores, unsigned int delimitador){
    bool res = false;
    for(unsigned int i = 0; i < delimitador; i++){
        if(color == colores[i]){
            res = true;
            break;
        }
    }
    return res;
}


vector<unsigned int> maximoImpactoExacto2(const Grafo &G, const Grafo &H){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;
    encontrado = false;

    vector<unsigned int> coloreo(G.cantNodos(),0);
    vector<unsigned int> colores(G.cantNodos());

    //Creo la lista de colores posibles
    for(unsigned int i = 0; i < colores.size(); i++){
        colores[i] = i+1;
    }

    maxImpactoPosible = calcLimiteImpacto(G,H);

    coloreo[0] = 1;
    colorear(1,G,H,coloreo,res);

    return res;
}

void colorear(unsigned int nodo, const Grafo &G, const Grafo &H, vector<unsigned int> &coloreo,vector<unsigned int> &solucion){

    if(nodo >= G.cantNodos()){
        unsigned int temp;
//        mostrarColoreo(coloreo);
        temp = H.impacto(coloreo);
        if(temp > solucion[0]){
            solucion[0] = temp;
            for(unsigned int k = 0; k < coloreo.size(); k++){
                solucion[k + 1] = coloreo[k];
            }
        }
//        if(solucion[0] == limite) encontrado = true;
        contador++;
    }
    else{
        unsigned int maxColor = *max_element(coloreo.begin(),coloreo.end());
        for(unsigned int c = 1; c <= (maxColor+1); c++){
            if(G.colorLegalDeNodo(nodo,coloreo,c)){
                vector<unsigned int> nuevoColoreo(coloreo);
                nuevoColoreo[nodo] = c;
                colorear(nodo+1,G,H,nuevoColoreo,solucion);
            }
        }
    }

}


void mostrarColoreo(const vector<unsigned int> &coloreo){
    for(unsigned int i = 0; i < coloreo.size(); i++){
        cout << " " << coloreo[i];
    }
    cout << endl;
}

unsigned int calcLimiteImpacto(const Grafo &G, const Grafo &H){
    unsigned int res = 0;
    unsigned int res2 = 0;
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
                    res2++;
                }
            }
        }
    }
    res = H.cantAristas() - res - (res2/2);
    return res;
}
