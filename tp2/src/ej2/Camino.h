#ifndef CAMINO_H
#define CAMINO_H


#include <iostream>
using namespace std;

class Camino
{
    public:
        Camino(unsigned int c1, unsigned int c2, bool existe, unsigned int costo);
        Camino(const Camino& other);
        unsigned int getCiudad1() const;
        unsigned int getCiudad2() const;
        bool getExiste() const;
        unsigned int getCosto() const;
        void imprimir() const;

        inline bool operator< (const Camino &b) const{
            if(getExiste() == b.getExiste()){
                if(getExiste()){
                    return getCosto() > b.getCosto();
                }
                else{
                    return getCosto() < b.getCosto();
                }
            }
            else{
                return getExiste();
            }
        }

    private:
        unsigned int ciudad1;
        unsigned int ciudad2;
        bool existe;
        unsigned int costo;

};

#endif // CAMINO_H
