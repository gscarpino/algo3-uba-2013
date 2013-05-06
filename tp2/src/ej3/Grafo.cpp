#include "Grafo.h"



Grafo::Grafo(unsigned int cantNodos){
    this->nodos = cantNodos;
    //evitamos realocacion de memoria
    this->aristas.reserve(cantNodos*cantNodos);
}

Grafo::Grafo(const Grafo& other)
{
    this->nodos = other.nodos;
    this->aristas = other.aristas;
}


unsigned int Grafo::getNodos(){
    return this->nodos;
}

vector< Camino > Grafo::getAristas(){
    return this->aristas;
}

//void Grafo::agregarArista(unsigned int n1, unsigned int n2, pair<bool,unsigned int> a){
//    if(n1 > this->nodos || n2 > this->nodos){
//        cerr << "Error: algun nodo no existente en el grafo" << endl;
//    }
//    else{
//        this->aristas.push_back(a);
//    }
//}

void Grafo::agregarArista(const Camino &c){
    this->aristas.push_back(c);
}

unsigned int Grafo::cantAristas() const{
    return this->aristas.size();
}

Grafo Grafo::AGM(){
    Grafo res(nodos);
    DisjointSet ds(this->nodos);
//    for(unsigned int i = 0; i < this->aristas.size(); i++){
//        this->aristas[i].imprimir();
//        cout << endl;
//    }

    //ordenar aristas grafo
    //e == 1 entonces de mayor a menor, e==0 entonces de menor a mayor

    sort(this->aristas.begin(),this->aristas.end());
//    cout << endl;
//    for(unsigned int i = 0; i < this->aristas.size(); i++){
//        this->aristas[i].imprimir();
//        cout << endl;
//    }

    //generar agm
    for(unsigned int i = 0; i < this->aristas.size(); i++){
        unsigned int c1 = this->aristas[i].getCiudad1();
        unsigned int c2 = this->aristas[i].getCiudad2();
        if(!ds.buscar(c1,c2)){
            Camino camino(c1,c2,this->aristas[i].getExiste(),this->aristas[i].getCosto());
            res.agregarArista(camino);
//            camino.imprimir();
            ds.unir(c1,c2);
            //Se puede agregar punto de corte m = n-1 pues es arbol
        }
    }

    return res;
}



