#include "DisjointSet.h"

DisjointSet::DisjointSet(unsigned int cant)
{
    for(unsigned int i = 0; i < cant; i++){
        this->clases[i] = i;
    }
}


void DisjointSet::unir(unsigned int x, unsigned int y){
    if(this->clases[x] != this->clases[y]){
        unsigned int nuevoID = this->clases[x];
        unsigned int viejoID = this->clases[y];
        for(map<int,int>::iterator it = this->clases.begin(); it != this->clases.end(); it++){
            if(it->second == viejoID){
                it->second = nuevoID;
            }
        }
    }
}

bool DisjointSet::buscar(unsigned int x, unsigned int y){
    bool res = false;
    res = this->clases[x] == this->clases[y];
    return res;
}


unsigned int DisjointSet::tamanio() const{
    return this->clases.size();
}

void DisjointSet::imprimir(){
    for(map<int,int>::iterator it = this->clases.begin(); it != this->clases.end(); it++){
        cout << "Clave " << it->first << ": " << it->second << endl;
    }
}
