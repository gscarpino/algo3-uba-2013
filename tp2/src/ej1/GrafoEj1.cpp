#include "GrafoEj1.h"


Grafo::Grafo(unsigned int cant) 	//constructor vacio, requiere la cantidad de nodos que vamos a poner
{

    this->cantNodos=cant;		//cantidad de nodos

    vector<unsigned int> vacio;
    this->aristas.reserve(cant);

    for(unsigned int i=0; i< cant; i++)
    {
        this->aristas.push_back(vacio);
    }

    this->cantAristas=0;


}

Grafo::Grafo(const Grafo& other)  //constructor por copia
{

    this->cantNodos = other.cantNodos;
    this->aristas = other.aristas;
    this->cantAristas = other.cantAristas;

}

void Grafo::agregarArista(const unsigned int u, const unsigned int v)   //requiere u >0
{

    this->aristas[u].push_back(v);
    this->cantAristas++;

}

bool Grafo::tieneHijos (unsigned int nodo)  	//requiere nodo>0  (en este ejercicio tiene sentido esperar nodo>0)
{

    return !(this->aristas[nodo].empty());
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

//Si el grafo es DAG, devuelve true y en el parametro de salida devuielve los nodos en orden topologico
// order: parametro de salida. valido solo si la funcion retorna true
//       order[i] = nodo en la posicion i correspondiente al orden topologico lineal
bool Grafo::ordenTopologico(vector<unsigned int> &nodosOrdenados)
{
    vector<unsigned int> marcas(cantNodos,ABIERTO);
    list<unsigned int> nodosOrdenadosTemp(cantNodos);
    int seleccionado = 0;

    while(seleccionado != -1)
    {
        seleccionado = buscarNodoAbierto(marcas);
        if(seleccionado != -1)
        {
            if(!visitar(seleccionado,marcas,nodosOrdenadosTemp))
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

bool Grafo::visitar(const unsigned int nodo, vector<unsigned int> &marcas,list<unsigned int> &nodosOrdenados)
{
    if(marcas[nodo] == PROCESADO)
    {
        // Se en
        //hay un ciclo
        return false;
    }
    else if(marcas[nodo] == ABIERTO)
    {
        marcas[nodo] = PROCESADO;
        for(unsigned int i = 0; i < this->aristas[nodo].size(); i++)
        {
            if(!visitar(aristas[nodo][i],marcas,nodosOrdenados))
            {
                return false;
            }
        }
        marcas[nodo] = CERRADO;
        nodosOrdenados.push_front(nodo);
    }
    return true;
}


int Grafo::buscarNodoAbierto(const vector<unsigned int> &marcas)
{
    int res = -1;
    for(unsigned int i = 0; i < marcas.size(); i++)
    {
        if(marcas[i] == ABIERTO)
        {
            res = i;
        }
    }
    return res;
}

int Grafo::caminoMaximo(vector<unsigned int> &camino)
{
    int n = this->cantNodos;
    vector<unsigned int> sucesorEnCamino(n); // sucesorEnCamino[i] = siguiente nodo en el camino mas largo desde i (0 indica fin)
    vector<unsigned int> nodosOrdenadosTopologicamente(n);
    // dist[i] es la longitud del camino simple mas largo entre el nodo incial
    // y el nodo i
    vector<int> dist(n);
    uint hijo;

    if(this->ordenTopologico(nodosOrdenadosTopologicamente))
    {   //Si tiene orden topologico:

         //Calculamos el mejor camino que nace en cada nodo
        for(int i = n-1; i > 0; i--)
        {
            uint v = nodosOrdenadosTopologicamente[i];
            dist[v] = 0;
            sucesorEnCamino[v] = 0; // Si el nodo no tiene hijos (no entra en el siguiente ciclo), es fin de camino.

            // calculamos la distancia buscando la maxima distancia de los anteriores
            for (unsigned int j = 0; j < (this->aristas[v]).size(); j++)
            {
                hijo = this->aristas[v][j];
                if((dist[hijo] + 1) > dist[v])
                {
                    dist[v] = dist[hijo] + 1;
                    sucesorEnCamino[v] =  hijo;
                }
            }
        }

        // Buscamos el nodo inicio del mejor camino
        int i, nodoInicio = 0;
        for(i = 0; i < dist.size(); i++)
        {
            if(dist[i] > dist[nodoInicio])
            {
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

        int maxDist = dist[nodoInicio];
        return maxDist;
    }
    else
    {
        return -1;
    }
}
