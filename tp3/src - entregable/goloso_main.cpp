#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Grafo.h"
#include "goloso.h"

using namespace std;

void mostrarColoreo(const vector<unsigned int> &coloreo);
void genTests();

int main(int argc, char * argv[])
{
    unsigned int nodos, aristasG, aristasH, v, u;
    unsigned int cont = 0;

    float porcentaje = 0.1;
    if(argc == 2)
    {
        porcentaje = atof(argv[1]);
    }

    while(!cin.eof() && cin.peek() != '#')
    {
        //COMIENZO Carga de datos
        cin >> nodos >> aristasG >> aristasH;

        Grafo grafoG(nodos);
        Grafo grafoH(nodos);

        for(unsigned int i = 0; i < aristasG; i++)
        {
            cin >> v >> u;
            grafoG.agregarArista(v-1,u-1);
        }

        for(unsigned int i = 0; i < aristasH; i++)
        {
            cin >> v >> u;
            grafoH.agregarArista(v-1,u-1);
        }

        // Quitamos el ultimo \n (para que cin.peek tome correctamente el siguiente caracter valido - numero o #)
        cin.get() ;
        // FIN Carga de datos

        cont++;

        mostrarColoreo(maximoImpactoGoloso(grafoG,grafoH, porcentaje));
    }
    return 0;
}

void mostrarColoreo(const vector<unsigned int> &coloreo)
{
    for(unsigned int i = 0; i < coloreo.size(); i++)
    {
        cout << coloreo[i];
        (i != coloreo.size()) ? cout << " " : cout << "";
    }
    cout << endl;
}
