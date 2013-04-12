#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <algorithm>
//#include <time.h>

//#define TESTING_AZAR 1

using namespace std;

int cuantosEntran(int n,int b, int h, int x, int y, const vector<int> &ptosx, const vector<int> &ptosy);
void resolver(const int &n, const int &b, const int &h, const vector<int> &x, const vector<int> &y, int &resx, int &resy, int &ptos);
bool estarep(const vector<int> &ptosx, const vector<int> &ptosy, int x, int y, int r);
timespec diff(timespec start, timespec end);


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
   char testear;
   int cantidad;		

   cout << "Algoritmos y Estructuras de Datos III - 2013 C1" << endl << "TP1 - Ejercicio 3: La caja en el plano" << endl << endl;

	cout<<"Desea crear casos de test aleatorios? y / n "<<endl;
	
	cin>>testear;
		

	

	if(testear=='y'){

	cout<<"Cuantos casos desea crear? Nota: se crearan casos desde 1 hasta el entero que introduzca"<<endl;
        cin>>cantidad;
	cout << "Creando tests..." << endl;	
	int base=0;
	int altura=0;
	vector<int> testx(cantidad);
	vector<int> testy(cantidad);
	int xtest=0;
	int ytest=0;
	bool repetido=0;
	
        ofstream archTesting("testingAzar.txt");
        if(archTesting.is_open()){
        	
		srand(time(NULL));
				
            
		for(int f=1; f <cantidad+1 ;f++){ // cantidad de puntos
                	
			base= rand() % 50 +1;
			altura= rand() % 50 + 1;
				
			archTesting <<f<<" "<<base<<" "<<altura<<endl;	
				
			for(int r = 0; r < f; r++){
				repetido=1;
				xtest= rand() % 500 + 1;
				ytest=rand() %500 +1;
				while(repetido && r!=0){		       		
					xtest= rand() % 500 + 1;
					ytest=rand() %500 +1;
					repetido=estarep(testx,testy, xtest, ytest, r);
				}
				
				testx[r]= xtest;
				testy[r]= ytest; 
		         	
	                        	
                    	}
		
			for (int o=0; o<f ; o++){			
			archTesting<<testx[o]<<" "<<testy[o]<<" ";
			}
		archTesting<<endl;
		archTesting << "#"<<endl;
                   
            	}
         
        }
        
        archTesting.close();

        cout << "Tests creados." << endl;
       
    }




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
	   
	
	    //timespec time1, time2;

	    //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);

            resolver(cantPtos,  base,   altura,   puntosx,   puntosy, resCajax,  resCajay,  resPtos);
	
	   //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	
	   //cout<<cantPtos<<" "<<diff(time1,time2).tv_sec<<"."<<diff(time1,time2).tv_nsec<<endl;
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
  
    for(int i=0; i<n; i++) {     //siempre chequea desde la esquina inferior izquierda---> x<= x_i <= x+b   , y<= y_i <= y+h
	
    	if ((x<=ptosx[i]) && (ptosx[i]<= (x+b)) && (y<=ptosy[i]) && (ptosy[i]<= (y+h))){
            cant++;

        }
    
    }

    return cant;
}

bool estarep(const vector<int> &ptosx, const vector<int> &ptosy, int x, int y, int r){

	bool esta=0;
	int i=0;		
	while (i<r && !esta){

	if (x==ptosx[i]){

		if (y==ptosy[i]) {
		
		esta=1;
		}	
	
	}
	i++;
		

	}
	return esta;
}

/*timespec diff(timespec start, timespec end)  //AUTOR = http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}*/
