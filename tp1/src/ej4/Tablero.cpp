#include "Tablero.h"


Tablero::Tablero(unsigned int rows, unsigned int cols){
    this->rows = rows;
    this->cols = cols;
    vector<pair<unsigned int, bool> > fila(cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            fila[j] = make_pair(0,false);
        }
        this->m.push_back(fila);
    }
}

Tablero::Tablero(const Tablero &otro){
    this->rows = otro.rows;
    this->cols = otro.cols;
    this->m = otro.m;
}

Tablero::Tablero(const Matriz &matriz, unsigned int rows, unsigned int cols){
    this->rows = rows;
    this->cols = cols;
    vector<pair<unsigned int, bool> > fila(this->cols);
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            fila[j] = make_pair(matriz[i][j],false);
        }
        this->m.push_back(fila);
    }
}

unsigned int Tablero::getRows() const{
    return this->rows;
}

unsigned int Tablero::getCols() const{
    return this->cols;
}


void Tablero::imprimir() const{
    for(unsigned int j = 0; j < cols; j++){
        cout << "_";
    }
    cout << endl;
    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            if(m[i][j].first){
                cout << " BLANCO ";
            }
            else{
                cout << " NEGRO  ";
            }
        }
        cout << endl;
    }
    for(unsigned int j = 0; j < cols; j++){
        cout << "_";
    }
    cout << endl;
}

void Tablero::imprimirConFichas() const{

    for(unsigned int j = 0; j < cols; j++){
        cout << "_";
    }
    cout << endl;
    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            Posicion p = make_pair(i,j);
            if(ocupado(p)){
                if(m[i][j].first){
                    cout << " NEGRO,OCUPADO ";
                }
                else{
                    cout << "BLANCO,OCUPADO ";
                }
            }
            else{
                if(m[i][j].first){
                    cout << " BLANCO,LIBRE  ";
                }
                else{
                    cout << "  NEGRO,LIBRE  ";
                }
            }
        }
        cout << endl;
    }
    for(unsigned int j = 0; j < cols; j++){
        cout << "_";
    }
    cout << endl;
}


bool Tablero::ocupado(const Posicion &pos) const{
    bool res = false;
    if(pos.first < rows && pos.second < cols){
        res = m[pos.first][pos.second].second;
    }
    return res;
}


vector<Posicion> Tablero::posiblesPosiciones(const Pieza &pieza) const{
    vector<Posicion> posiciones;
    Posicion p;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            p = make_pair(i,j);
            if(encaja(pieza,p)){
                posiciones.push_back(p);
            }
        }
    }
    return posiciones;
}


void Tablero::ubicarFicha(const Pieza &pieza, const Posicion &pos){
    for(unsigned int i = 0; i < pieza.getRows(); i++){
        for(unsigned int j = 0; j < pieza.getCols(); j++){
            m[pos.first + i][pos.second + j].second = true;
        }
    }
}


bool Tablero::encaja(const Pieza &pieza, const Posicion &pos) const{
    bool res = true;
    Posicion p;
    for(unsigned int i = 0; i < pieza.getRows(); i++){
        for(unsigned int j = 0; j < pieza.getCols(); j++){
            p = make_pair(pos.first + i,pos.second + j);
            if((p.first < rows) && (p.second < cols) && (res)){
                res = res && (m[p.first][p.second].first == pieza.getColor(i,j)) && (!ocupado(p));
            }
            else{
                return false;
            }
        }
    }
    return res;
}


bool Tablero::completo() const{
    bool res = true;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            res = res && m[i][j].second;
        }
    }
    return res;
}


Tablero& Tablero::operator=(const Tablero &otro){
    m = otro.m;
    rows = otro.rows;
    cols = otro.cols;
    return *this;
}

