#include "Pieza.h"

Pieza::Pieza(const Matriz &p, const unsigned int id){
    //Requiere matriz no vacia
    this->m = p;
    this->rows = p.size();
    this->cols = p[0].size();
    this->id = id;
}

Pieza::Pieza(const Pieza &otra){
    this->m = otra.m;
    this->rows = otra.rows;
    this->cols = otra.cols;
    this->id = otra.id;
}

void Pieza::imprimir() const{
    for(unsigned int j = 0; j < 11; j++){
        if(j == 5){
            cout << " " << this->id << " ";
        }
        else{
            cout << " * ";
        }
    }
    cout << endl;
    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            if(m[i][j]){
                cout << " BLANCO ";
            }
            else{
                cout << " NEGRO  ";
            }
        }
        cout << endl;
    }
    for(unsigned int j = 0; j < 11; j++){
        cout << " * ";
    }
    cout << endl;
}



unsigned int Pieza::getRows() const{
    return this->rows;
}

unsigned int Pieza::getCols() const{
    return this->cols;
}

unsigned int Pieza::getID() const{
    return this->id;
}


unsigned int Pieza::getColor(const unsigned int x, const unsigned int y) const{
    return m[x][y];
}

unsigned int Pieza::getColor(const Posicion &p) const{
    return m[p.first][p.second];
}


Pieza Pieza::rotar() const{
    Matriz forma;
    Vec fila(rows);

    for(unsigned int i = 0; i < cols; i++){
        for(unsigned int j = 0; j < rows; j++){
            fila[j] = m[j][i];
        }
        forma.push_back(fila);
    }

    Pieza res(forma,id);
    return res;
}

bool operator<(const Pieza &p1, const Pieza &p2){
    //Necesario para poder buscar todas las permutaciones posibles
    return p1.id < p2.id;
}

bool operator!=(const Pieza &p1, const Pieza &p2){
    //Necesario para poder buscar todas las permutaciones posibles
    bool res = true;
    if(p1.id == p2.id){
        if(p1.getRows() == p2.getRows()){
            if(p1.getCols() == p2.getCols()){
                if(p1.m == p2.m){
                    res = false;
                }
            }
        }
    }
    return res;
}

Pieza& Pieza::operator=(const Pieza &otro){
    m = otro.m;
    rows = otro.rows;
    cols = otro.cols;
    id = otro.id;
    return *this;
}
