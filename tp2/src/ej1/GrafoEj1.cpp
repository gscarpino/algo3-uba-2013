#include "GrafoEj1.h"

Grafo::Grafo(unsigned int cant) 	//constructor vacio, requiere la cantidad de nodos que vamos a poner
{
    this->cantNodos=cant;
    this->cantAristas=0;

    vector<unsigned int> vacio;
    this->aristas.reserve(cant);

    // Agregamos un primer nodo 0, para poder referenciar al resto
    // por su numero sin preocuparnos por cambiar indices
    this->aristas.push_back(vacio);
    for(unsigned int i=0 ; i < cant ; i++)
    {
        this->aristas.push_back(vacio);
    }

    // Marcamos todos los nodos como ABIERTOS
    this->marcas.reserve(cantNodos+1);
    for(uint i = 1; i <= cantNodos; i++)
    {
        this->marcas[i] = ABIERTO;
    }
}

Grafo::Grafo(const Grafo& other)  //constructor por copia
{
    this->cantNodos = other.cantNodos;
    this->aristas = other.aristas;
    this->cantAristas = other.cantAristas;
    this->marcas = other.marcas;
}

void Grafo::agregarArista(const unsigned int u, const unsigned int v)   //requiere u >0
{

    this->aristas[u].push_back(v);
    this->cantAristas++;

}

unsigned int Grafo::cantidadNodos()
{
    return cantNodos;
}

unsigned int Grafo::cantidadAristas()
{
    return cantAristas;
}

vector<unsigned int> Grafo::hijos(unsigned int nodo)
{
    return this->aristas[nodo];
}

//Si el grafo es DAG, devuelve true y en el parametro de salida devuelve los nodos en orden topologico
// nodosOrdenados: parametro de salida. valido solo si la funcion retorna true
//       nodosOrdenados[i] = nodo en la posicion i correspondiente al orden topologico lineal
bool Grafo::ordenTopologico(vector<unsigned int> &nodosOrdenados)
{
    list<unsigned int> nodosOrdenadosTemp(cantNodos);
    int seleccionado = 0;

    while(seleccionado != -1)
    {
        seleccionado = buscarNodoAbierto();
        if(seleccionado != -1)
        {
            if(!visitar(seleccionado, nodosOrdenadosTemp))
            {
                return false;
            }
        }
    }

    // Transformamos la lista en un vector, por practicidad en
    // los algoritmos que usan este resultado
    for(unsigned int i = 0; i < nodosOrdenadosTemp.size(); i++)
    {
        nodosOrdenados[i] = (nodosOrdenadosTemp.front());
        nodosOrdenadosTemp.pop_front();
    }
    return true;
}

bool Grafo::visitar(const unsigned int nodo, list<unsigned int> &nodosOrdenados)
{
    if(this->marcas[nodo] == DESCUBIERTO)
    {
        //hay un ciclo
        return false;
    }
    else if(this->marcas[nodo] == ABIERTO)
    {
        this->marcas[nodo] = DESCUBIERTO;
        for(unsigned int i = 0; i < this->aristas[nodo].size(); i++)
        {
            if(!visitar(aristas[nodo][i], nodosOrdenados))
            {
                return false;
            }
        }
        this->marcas[nodo] = CERRADO;
        nodosOrdenados.push_front(nodo);
    }
    return true;
}


int Grafo::buscarNodoAbierto()
{
    int res = -1;
    for(unsigned int i = 1; i <= this->cantidadNodos(); i++)
    {
        if(this->marcas[i] == ABIERTO)
        {
            res = i;
        }
    }
    return res;
}

// caminoMaximo: devuelve la longitud del camino de mayor longitud que se encuentra en el digrafo (si es un DAG).
//               Si no es un DAG, devuelve -1.
// parametros:
//    * camino: parametro de salida. Valido solo si el digrafo es un DAG.
int Grafo::caminoMaximo(vector<unsigned int> &camino)
{
    int n = this->cantNodos;

    vector<unsigned int> nodosOrdenadosTopologicamente(n);

    //los siguientes vectores se indexan por nodo (por eso son de tamaño n+1, los nodos van de 1 a n)
    vector<unsigned int> sucesorEnCamino(n+1); // sucesorEnCamino[i] = siguiente nodo en el camino mas largo desde i (0 indica fin)
    vector<int> longitud(n+1); // longitud[i] es la longitud del camino simple mas largo desde i

    uint sucesor;

    if(this->ordenTopologico(nodosOrdenadosTopologicamente))
    {
        // Si tiene orden topologico (es un DAG):

        // Para cada nodo, calculamos el mejor camino que lo tiene como origen
        // Recorremos el orden topologico en sentido inverso
        for(int i = n-1; i >= 0; i--)
        {
            uint v = nodosOrdenadosTopologicamente[i];
            longitud[v] = 0;
            sucesorEnCamino[v] = 0; // Si el nodo no tiene hijos (no entra en el siguiente ciclo), es fin de camino.

            // calculamos la distancia buscando la maxima distancia de los sucesores
            for (unsigned int j = 0; j < (this->aristas[v]).size(); j++)
            {
                sucesor = this->aristas[v][j];
                if((longitud[sucesor] + 1) > longitud[v])
                {
                    longitud[v] = longitud[sucesor] + 1;
                    sucesorEnCamino[v] =  sucesor;
                }
            }
        }

        // Buscamos el nodo inicio del mejor camino
        uint i, nodoInicio = 1;
        for(i = 1; i < longitud.size(); i++)
        {
            if(longitud[i] > longitud[nodoInicio])
            {
                //
                nodoInicio = i;
            }
        }

        // Armamos el camino
        i = nodoInicio;
        camino.push_back(nodoInicio);
        while(sucesorEnCamino[i] != 0)
        {
            i = sucesorEnCamino[i];
            camino.push_back(i);
        }

        int maxDist = longitud[nodoInicio];
        return maxDist;
    }
    else
    {
        return -1;
    }
}
