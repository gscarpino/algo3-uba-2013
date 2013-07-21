#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <cmath>

#include "Grafo.h"
#include "exacto.h"
#include "goloso.h"
#include "local.h"
#include "grasp.h"

#define TESTING 0
#define RES_EFECTIVIDAD 0
#define RES_EFECTIVIDAD2 0
#define RES_TIMING 1
#define RES_Goloso 0
#define RES_Grasp 0

using namespace std;

void genTests();

timespec diff(timespec start, timespec end){
        timespec temp;
        if ((end.tv_nsec-start.tv_nsec)<0) {
                temp.tv_sec = end.tv_sec-start.tv_sec-1;
                temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
        } else {
                temp.tv_sec = end.tv_sec-start.tv_sec;
                temp.tv_nsec = end.tv_nsec-start.tv_nsec;
        }
        return temp;
}
void borrarElemento(vector<unsigned int> &v, unsigned int e);

int main(int argc, char * argv[])
{

    cout << "Algoritmos y Estructuras de Datos III - 2013 C1" << endl;
    cout << "TP3: Coloreo y Maximo impacto" << endl << endl;

    srand(time(NULL));
    if(TESTING)
    {
        genTests();
        return 0;
    }

    ofstream resEfect;
    ofstream resEfect2;
    ofstream resGoloso;
    ofstream resGrasp;
    ofstream resTiming;
    if(RES_EFECTIVIDAD)
    {
        resEfect.open("Resultado_Efectividad.csv",  ios_base::trunc);
        if(!resEfect.is_open())
        {
            cerr << "Error al abrir/crear el archivo de salida." << endl;
            exit(1);
        }
        resEfect << "Nodos Exacto Goloso BusquedaLocal Grasp" << endl;
    }

    if(RES_TIMING)
    {
        resTiming.open("Resultado_tiempos.csv",  ios_base::trunc);
        if(!resTiming.is_open())
        {
            cerr << "Error al abrir/crear el archivo de salida." << endl;
            exit(1);
        }
        resTiming << "Nodos Grasp Goloso BLocal" << endl;
    }

    if(RES_EFECTIVIDAD2)
    {
        resEfect2.open("Resultado_Efectividad2.csv",  ios_base::trunc);
        if(!resEfect2.is_open())
        {
            cerr << "Error al abrir/crear el archivo de salida." << endl;
            exit(1);
        }
        resEfect2 << "Nodos Grasp Goloso BusquedaLocal" << endl;
    }

    if(RES_Goloso)
    {
        resGoloso.open("Resultado_Goloso.csv",  ios_base::trunc);
        if(!resGoloso.is_open())
        {
            cerr << "Error al abrir/crear el archivo de salida." << endl;
            exit(1);
        }
        resGoloso << "Nodos Grasp 0 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9 0.95 1" << endl;
    }
    if(RES_Grasp)
    {
        resGrasp.open("Resultado_Grasp.csv",  ios_base::trunc);
        if(!resGrasp.is_open())
        {
            cerr << "Error al abrir/crear el archivo de salida." << endl;
            exit(1);
        }
        resGrasp << "Nodos 0 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9 0.95 1" << endl;
    }



    unsigned int efectividadGoloso = 0;
    unsigned int efectividadGolosoAcertado = 0;

    unsigned int efectividadLocal = 0;
    unsigned int efectividadLocalAcertado = 0;

    unsigned int efectividadGrasp = 0;
    unsigned int efectividadGraspAcertado = 0;
    unsigned int cont = 0;

    unsigned int nodos;
    unsigned int aristasG;
    unsigned int aristasH;
    unsigned int v;
    unsigned int u;

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
        cout << endl << "N " << nodos << " R " << cont << endl;
        if(!RES_Goloso && !RES_Grasp && !RES_EFECTIVIDAD2 && !RES_TIMING){
            double porcentaje = 0;
            vector<unsigned int> impactoExacto(maximoImpactoExacto(grafoG,grafoH));
            vector<unsigned int> impactoGoloso(maximoImpactoGoloso(grafoG,grafoH,porcentaje));
            vector<unsigned int> impactoLocal(maximoImpactoLocal(grafoG,grafoH,impactoGoloso));
            vector<unsigned int> impactoGrasp(maximoImpactoGrasp(grafoG,grafoH,porcentaje));

            if(abs(impactoExacto[0]- impactoGoloso[0]) == 0) efectividadGolosoAcertado++;
            if(abs(impactoExacto[0]- impactoGoloso[0]) <= 1) efectividadGoloso++;
            if(abs(impactoExacto[0]- impactoLocal[0]) == 0) efectividadLocalAcertado++;
            if(abs(impactoExacto[0]- impactoLocal[0]) <= 1) efectividadLocal++;
            if(abs(impactoExacto[0]- impactoGrasp[0]) == 0) efectividadGraspAcertado++;
            if(abs(impactoExacto[0]- impactoGrasp[0]) <= 1) efectividadGrasp++;

            if(RES_EFECTIVIDAD){
                resEfect << nodos << " " << impactoExacto[0] << " " << impactoGoloso[0] << " " << impactoLocal[0] << " " << impactoGrasp[0] << endl;
            }
            else{
//                cout << "Exacto: " << impactoExacto[0] << endl;
//                cout << "Goloso: " << impactoGoloso[0] << endl;
//                cout << "Local: " << impactoLocal[0] << endl;
//                cout << "Grasp: " << impactoGrasp[0] << endl;
//                cout << endl;
            }
        }

        if(RES_Goloso){
            vector<unsigned int> impactoGrasp2(maximoImpactoGrasp(grafoG,grafoH,0.4));
            resGoloso << nodos << " " << impactoGrasp2[0];
            for(unsigned int parametro = 0; parametro <= 100; parametro+=5)
            {
                vector<unsigned int> impactoGoloso2(maximoImpactoGoloso(grafoG,grafoH,parametro/100.0));
                resGoloso << " " << impactoGoloso2[0];
            }
            resGoloso << endl;
        }

        if(RES_Grasp){
            resGrasp << nodos;
            for(unsigned int parametro = 5; parametro <= 100; parametro+=5)
            {
                vector<unsigned int> impactoGrasp2(maximoImpactoGrasp(grafoG,grafoH,parametro/10.0));
                resGrasp << " " << impactoGrasp2[0];
            }
            resGrasp << endl;
        }

        if(RES_TIMING){
            timespec comienzo;
            timespec terminacion;
            resTiming << nodos;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
//            vector<unsigned int> impactoGrasp(maximoImpactoGrasp(grafoG,grafoH,0.0));
            vector<unsigned int> impactoGrasp(maximoImpactoExacto(grafoG,grafoH));
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);
            resTiming << " " << diff(comienzo,terminacion).tv_nsec;

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
//            vector<unsigned int> impactoGoloso(maximoImpactoGoloso(grafoG,grafoH,0.0));
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);
            resTiming << " " << diff(comienzo,terminacion).tv_nsec;

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &comienzo);
//            vector<unsigned int> impactoLocal(maximoImpactoLocal(grafoG,grafoH,0.0));
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &terminacion);
            resTiming << " " << diff(comienzo,terminacion).tv_nsec << endl;
        }

        if(RES_EFECTIVIDAD2){
            double porcentaje = 0.1;
            vector<unsigned int> impactoGoloso(maximoImpactoGoloso(grafoG,grafoH,porcentaje));
            vector<unsigned int> impactoLocal(maximoImpactoLocal(grafoG,grafoH,impactoGoloso));
            vector<unsigned int> impactoGrasp(maximoImpactoGrasp(grafoG,grafoH,porcentaje));
            resEfect2 << nodos << " " << impactoGrasp[0] << " " << impactoGoloso[0] << " " << impactoLocal[0] << endl;
        }


    }

    cout << endl << "Efectividad Goloso: " << ((double)efectividadGoloso/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Goloso acertando: " << ((double)efectividadGolosoAcertado/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Local: " << ((double)efectividadLocal/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Local acertando: " << ((double)efectividadLocalAcertado/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Grasp: " << ((double)efectividadGrasp/(double)cont) * 100 << "%" << endl;
    cout << endl << "Efectividad Grasp acertando: " << ((double)efectividadGraspAcertado/(double)cont) * 100 << "%" << endl;

    resEfect.close();
    resGoloso.close();
    resTiming.close();
    resGrasp.close();
    resEfect2.close();

    cout << endl << "Termino" << endl;
    return 0;
}


void genTests(){
    ofstream outputFile;
    unsigned int minNodos = 5;
    unsigned int maxNodos = 15;
    unsigned int repeticiones = 50;
    int prob = 30;

    cout << "Creando test G y H al azar" << endl;
    outputFile.open("testAzar.txt",  ios_base::trunc);
    if(!outputFile.is_open())
    {
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    for(unsigned int nodos = minNodos; nodos <= maxNodos; nodos++)
    {
        for(unsigned int r = 0; r < repeticiones; r++)
        {
            vector<pair<unsigned int, unsigned int> > vecinosG;
            vector<pair<unsigned int, unsigned int> > vecinosH;
            for(unsigned int i = 0; i < nodos; i++)
            {
                for(unsigned int j = i+1; j < nodos; j++)
                {
                    if(rand()%100 < prob)
                    {
                        vecinosG.push_back(make_pair(i+1,j+1));
                    }
                    if(rand()%100 < prob)
                    {
                        vecinosH.push_back(make_pair(i+1,j+1));
                    }
                }
            }
            outputFile << nodos << " " << vecinosG.size() << " " << vecinosH.size()<< endl;
            for(unsigned int i = 0; i < vecinosG.size(); i++)
            {
                outputFile << vecinosG[i].first << " " << vecinosG[i].second << endl;
            }
            for(unsigned int i = 0; i < vecinosH.size(); i++)
            {
                outputFile << vecinosH[i].first << " " << vecinosH[i].second << endl;
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Test creado." << endl;

    //Minimo 5 nodos
    cout << "Creando test G y H estrella" << endl;
    outputFile.open("testStar.txt",  ios_base::trunc);
    if(!outputFile.is_open())
    {
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    for(unsigned int nodos = minNodos; nodos <= maxNodos; nodos++) {
        for(unsigned int r = 0; r < repeticiones; r++) {
            vector<pair<unsigned int, unsigned int> > vecinosG;
            vector<pair<unsigned int, unsigned int> > vecinosH;
            vector<unsigned int> gradoUno;

            vecinosG.push_back(make_pair(1,2));
            vecinosG.push_back(make_pair(1,3));
            vecinosG.push_back(make_pair(1,4));
            vecinosG.push_back(make_pair(1,5));

            gradoUno.push_back(1);
            gradoUno.push_back(2);
            gradoUno.push_back(3);
            gradoUno.push_back(4);
            gradoUno.push_back(5);

            for(unsigned int i=5; i < nodos; i++){
                unsigned int elegido = rand()%((unsigned int)(gradoUno.size()*1.3));
                if(elegido >= gradoUno.size()){
                    elegido = 0;
                }
                vecinosG.push_back(make_pair(gradoUno[elegido],i+1));
                if(gradoUno[elegido] != 1){
                    borrarElemento(gradoUno,gradoUno[elegido]);
                }
                gradoUno.push_back(i+1);
            }


            for(unsigned int i = 0; i < nodos; i++) {
                for(unsigned int j = i+1; j < nodos; j++) {
                    if(rand()%100 < prob) {
                        vecinosH.push_back(make_pair(i+1,j+1));
                    }
                }
            }
            outputFile << nodos << " " << vecinosG.size() << " " << vecinosH.size()<< endl;
            for(unsigned int i = 0; i < vecinosG.size(); i++) {
                outputFile << vecinosG[i].first << " " << vecinosG[i].second << endl;
            }
            for(unsigned int i = 0; i < vecinosH.size(); i++) {
                outputFile << vecinosH[i].first << " " << vecinosH[i].second << endl;
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Test creado." << endl;

    //Minimo 5 nodos
    cout << "Creando test G y H Web" << endl;
    outputFile.open("testWeb.txt",  ios_base::trunc);
    if(!outputFile.is_open())
    {
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    for(unsigned int nodos = minNodos; nodos <= maxNodos; nodos++) {
        for(unsigned int r = 0; r < repeticiones; r++) {
            vector<pair<unsigned int, unsigned int> > vecinosG;
            vector<pair<unsigned int, unsigned int> > vecinosH;
            vector<unsigned int> externos;

            vecinosG.push_back(make_pair(1,2));
            vecinosG.push_back(make_pair(1,3));
            vecinosG.push_back(make_pair(1,4));
            vecinosG.push_back(make_pair(1,5));

            externos.push_back(2);
            externos.push_back(3);
            externos.push_back(4);
            externos.push_back(5);

            for(unsigned int i=5; i < nodos; i++){
                unsigned int elegido = (i-1)%4;
                vecinosG.push_back(make_pair(externos[elegido],i+1));
                if(elegido == 3){
                    for(unsigned int j = 0; j < externos.size(); j++){
                        vecinosG.push_back(make_pair(externos[j],externos[(j+1)%externos.size()]));
                    }
                    externos.clear();
                    externos.push_back(i-2);
                    externos.push_back(i-1);
                    externos.push_back(i);
                    externos.push_back(i+1);
                }
            }

            for(unsigned int i = 0; i < nodos; i++) {
                for(unsigned int j = i+1; j < nodos; j++) {
                    if(rand()%100 < prob) {
                        vecinosH.push_back(make_pair(i+1,j+1));
                    }
                }
            }
            outputFile << nodos << " " << vecinosG.size() << " " << vecinosH.size()<< endl;
            for(unsigned int i = 0; i < vecinosG.size(); i++) {
                outputFile << vecinosG[i].first << " " << vecinosG[i].second << endl;
            }
            for(unsigned int i = 0; i < vecinosH.size(); i++) {
                outputFile << vecinosH[i].first << " " << vecinosH[i].second << endl;
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Test creado." << endl;

}

void borrarElemento(vector<unsigned int> &v, unsigned int e){
    for(unsigned int i = 0; i < v.size(); i++){
        if(v[i] == e){
            v.erase(v.begin() + i);
            break;
        }
    }
}
