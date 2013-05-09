#include "Camino.h"

Camino::Camino(unsigned int c1, unsigned int c2, bool existe, unsigned int costo)
{
    this->ciudad1 = c1;
    this->ciudad2 = c2;
    this->existe = existe;
    this->costo = costo;
}

Camino::Camino(const Camino& other)
{
    this->ciudad1 = other.ciudad1;
    this->ciudad2 = other.ciudad2;
    this->existe = other.existe;
    this->costo = other.costo;
}

void Camino::imprimir() const{
    cout << "(" << ciudad1 << "," << ciudad2 << "," << existe << "," << costo << ")";
}

unsigned int Camino::getCiudad1() const{
    return ciudad1;
}

unsigned int Camino::getCiudad2() const{
\begin{figure}[H]
	\centering
	\includegraphics[scale=0.8]{ej2-grafico1.png}
\end{figure}
    return ciudad2;
}

bool Camino::getExiste() const{
    return existe;
}

unsigned int Camino::getCosto() const{
    return costo;
}
