#include "grasp.h"

vector<unsigned int> maximoImpactoGrasp(const Grafo &G, const Grafo &H, double porcentaje){
    vector<unsigned int> res(G.cantNodos() + 1);
    res[0] = 0;

    vector<unsigned int> coloreo(G.cantNodos(),1);

    //Criterios de parada
    unsigned int maxIteraciones = 250;
    unsigned int maxIterSinMejora = 75;
    unsigned int sinMejora = 0;
    unsigned int maxRCL = 5;
    unsigned int elegido;
    unsigned int solTemporal = 0;



    for(unsigned int i = 0; i < maxIteraciones; i++){

        vector< vector<unsigned int> > rcl(maxRCL);
        for(unsigned int k = 0; k < maxRCL; k++){
            rcl[k] = maximoImpactoGoloso(G,H,porcentaje);
        }

        elegido = rand()%maxRCL;

        vector<unsigned int> solBusqLocal;

        solBusqLocal = maximoImpactoLocal(G,H,rcl[elegido]);

        if(solBusqLocal[0] > solTemporal){
            res[0] = solBusqLocal[0];
            for(unsigned int k = 0; k < coloreo.size(); k++){
                res[k + 1] = coloreo[k];
            }
            solTemporal = solBusqLocal[0];
            sinMejora = 0;
        }
        else{
            sinMejora++;
            if(sinMejora == maxIterSinMejora){
                break;
            }
        }
    }

    return res;
}
