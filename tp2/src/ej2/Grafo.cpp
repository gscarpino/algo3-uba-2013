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


void Grafo::agregarArista(const Camino &c){
    this->aristas.push_back(c);
}

unsigned int Grafo::cantAristas() const{
    return this->aristas.size();
}

Grafo Grafo::AGM(){
    Grafo res(nodos);
    DisjointSet ds(this->nodos);

    //ordenar aristas grafo
    //e == 1 entonces de mayor a menor, e==0 entonces de menor a mayor
    sort(this->aristas.begin(),this->aristas.end());

    //generar agm
    for(unsigned int i = 0; i < this->aristas.size(); i++){
        unsigned int c1 = this->aristas[i].getCiudad1();
        unsigned int c2 = this->aristas[i].getCiudad2();
        if(!ds.buscar(c1,c2)){
            Camino camino(c1,c2,this->aristas[i].getExiste(),this->aristas[i].getCosto());
            res.agregarArista(camino);
            ds.unir(c1,c2);
        }
        if(res.cantAristas() == (res.getNodos()-1)){
            break;
        }
    }

    return res;
}



