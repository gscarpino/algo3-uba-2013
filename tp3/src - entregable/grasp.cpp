#include "grasp.h"
#include "goloso.h"
#include "local.h"

vector<unsigned int> maximoImpactoGrasp(const Grafo &G, const Grafo &H, double porcentaje)
{
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;

    vector<unsigned int> coloreo(G.cantNodos(),1);

    //Criterios de parada
    //Optimizados
    unsigned int maxIteraciones;
    unsigned int maxIterSinMejora;
    if(G.cantNodos() < 50)
    {
        maxIteraciones = G.cantNodos() * 10;
        maxIterSinMejora = maxIteraciones * 0.2;
    }
    else
    {
        maxIteraciones = G.cantNodos() * 3;
        maxIterSinMejora = maxIteraciones * 0.5;
    }
    //Optimizados
    unsigned int sinMejora = 0;
    unsigned int maxRCL = 5;
    unsigned int elegido;

    //Optimización del parámetro
    if(G.cantNodos() < 75)
    {
        porcentaje = 0.3;
    }
    else
    {
        porcentaje = 0.1;
    }



    for(unsigned int i = 0; i < maxIteraciones; i++)
    {

        vector< vector<unsigned int> > rcl(maxRCL);
        for(unsigned int k = 0; k < maxRCL; k++)
        {
            rcl[k] = maximoImpactoGoloso(G,H,porcentaje);
        }
        elegido = rand()%maxRCL;

        vector<unsigned int> solBusqLocal;

        solBusqLocal = maximoImpactoLocal(G,H,rcl[elegido]);

        if(solBusqLocal[0] > res[0])
        {
            res[0] = solBusqLocal[0];
            for(unsigned int k = 1; k < solBusqLocal.size(); k++)
            {
                res[k] = solBusqLocal[k];
            }
            sinMejora = 0;
        }
        else
        {
            sinMejora++;
            if(sinMejora == maxIterSinMejora)
            {
                break;
            }
        }
    }

    return res;
}
