#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;
void genTests(unsigned int minNodos,unsigned int maxNodos,unsigned int repeticiones,unsigned int prob);

int main(int argc, char * argv[])
{
    unsigned int minNodos = 3;
    unsigned int maxNodos = 16;
    unsigned int repeticiones = 100;
    int prob = 50;

    if(argc == 5)
    {
        minNodos = (unsigned int)atoi(argv[1]);
        maxNodos = (unsigned int)atoi(argv[2]);
        repeticiones = (unsigned int)atoi(argv[3]);
        prob = (unsigned int)atoi(argv[4]);
    }

    genTests(minNodos, maxNodos, repeticiones, prob);
    return 0;
}


void genTests(unsigned int minNodos,unsigned int maxNodos,unsigned int repeticiones,unsigned int prob){
    ofstream outputFile;

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

    prob = 75;

    cout << "Creando test G y H densos" << endl;
    outputFile.open("GyHdensos.txt",  ios_base::trunc);
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

    prob = 50;

    cout << "Creando test H complemento de G" << endl;
    outputFile.open("conHcomplemento.txt",  ios_base::trunc);
    if(!outputFile.is_open())
    {
        cerr << "Error al abrir/crear el archivo de salida." << endl;
        exit(1);
    }

    for(unsigned int nodos = minNodos; nodos <= maxNodos; nodos++)
    {
        for(unsigned int r = 0; r < repeticiones; r++)
        {
            unsigned int cont = 0;
            vector<vector<bool> > vecinosG;

            for(unsigned int i = 0; i < nodos; i++)
            {
                vector<bool> temp(nodos,false);
                vecinosG.push_back(temp);
                for(unsigned int j = i+1; j < nodos; j++)
                {
                    if(rand()%100 < prob)
                    {
                        vecinosG[i][j] = true;
                        cont++;
                    }
                }
            }
            outputFile << nodos << " " << cont << " " << (nodos*nodos - nodos - cont*2)/2 << endl;
            for(unsigned int i = 0; i < nodos; i++)
            {
                for(unsigned int j = i+1; j < nodos; j++)
                {
                    if(vecinosG[i][j])
                    {
                        outputFile << i+1 << " " << j+1 << endl;
                    }
                }
            }
            for(unsigned int i = 0; i < nodos; i++)
            {
                for(unsigned int j = i+1; j < nodos; j++)
                {
                    if(!vecinosG[i][j])
                    {
                        outputFile << i+1 << " " << j+1 << endl;
                    }
                }
            }
        }
    }

    outputFile << "#";
    outputFile.close();
    cout << "Test creado." << endl;
}
