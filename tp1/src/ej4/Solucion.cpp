#include "Sol.h"


Sol::Sol(){
    id = 0;
    rotaciones = 0;
    posicion = make_pair(0,0);
}


Sol::Sol(int id, int rotaciones, Posicion posicion){
    this->id = id;
    this->rotaciones = rotaciones;
    this->posicion = posicion;
}

void Sol::imprimir() const{
    cout << "<" << this->id << "," << this->rotaciones << ",(" << this->posicion.first << "," << this->posicion.second << ")>";
}
