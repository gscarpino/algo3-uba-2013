#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int cuantosEntran(int n,int b, int h, int x, int y, const vector<int> &ptosx, const vector<int> &ptosy);
void resolver(const int &n, const int &b, const int &h, const vector<int> &x, const vector<int> &y, int &resx, int &resy, int &ptos);


int main(int argc, char *argv[]) {

    if(argc <= 1) {
      cout << "Modo de uso: ej3 archivoEntrada archivoSalida";
      return 0;
    }

    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cerr << "Error al abrir el archivo de entrada." << endl;
    }

    ofstream outputFile(argv[2],  ios_base::trunc);
    if(!outputFile.is_open()){
        cerr << "Error al abrir/crear el archivo de salida." << endl;
    }

   string linea;
   int tiempoMinimo;


   cout << "Algoritmos y Estructuras de Datos III - 2013 C1" << endl << "TP1 - Ejercicio 3: La caja en el plano" << endl << endl;

    while(!inputFile.eof()){                  
        getline(inputFile, linea);
        
        if(linea == "#"){
		        getline(inputFile, linea);	        
	      }
	
        if(!inputFile.eof()){
        
            istringstream sLinea(linea);
            int cantPtos;
            int base;
            int altura;

            int n=0;
            int i=0;

            while(i<3){

                sLinea >> n;
                if (i==0) cantPtos=n;                             //cantidad de puntos
                if (i==1) base=n;                                 //base y altura de la caja
                if (i==2) altura=n;
                i++;
            
            }

            getline(inputFile, linea); 
                                                  

           //vector<pair<int, int> > puntos(cantPtos);
            vector<int> puntosx(cantPtos);    //en la posición i, esta la coordenada x del punto i
            vector<int> puntosy(cantPtos);      //en la posición i, esta la coordenada y del punto i
          
            istringstream sLinea2(linea);


            i=0;
            int x=0;
            int y=0;

            while(i<cantPtos){                            //cargo los puntos

                sLinea2 >>x;
                sLinea2 >>y;

                puntosx[i]=x;
                puntosy[i]=y;

                i++;

            }

            int resCajax;
            int resCajay;
            int resPtos;

            resolver(cantPtos,  base,   altura,   puntosx,   puntosy, resCajax,  resCajay,  resPtos);

            outputFile<<resCajax<<" "<<resCajay<<" "<<resPtos<<endl;
         

        } 
    } 

	cout<<"Fin del Programa"<<endl;

}



void resolver(const int &n, const int &b, const int &h, const vector<int> &x, const vector<int> &y, int &resx, int &resy, int &ptos){


    int cant=0;
    int m=0;
    resx=x[0];
    resy=y[0];

    for (int i=0; i < n; i++){

        for (int j=0; j< n; j++){
         
            m=cuantosEntran(n, b, h, x[i], y[j], x, y);
           
            if (cant<m){
                
                cant=m;
                resx=x[i];
                resy=y[j];
           
            }
        
        }
    
    }


    ptos= cant;


}


int cuantosEntran(int n, int b, int h,  int x, int y, const vector<int> &ptosx, const vector<int> &ptosy){


  int cant=0;
  bool entra=0;
  for(int i=0; i<n; i++) {     //siempre chequea desde la esquina inferior izquierda---> x<= x_i <= x+b   , y<= y_i <= y+h

   	
	
	if ((x<=ptosx[i]) && (ptosx[i]<= (x+b)) && (y<=ptosy[i]) && (ptosy[i]<= (y+h))){
     
  	
	

        cant++;

      }

    

  }

  return cant;
}
