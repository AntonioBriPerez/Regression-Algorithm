
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>

using namespace std;

/*Crea el fichero con puntos aleatorios.
Pasamos nº puntos por parámetro.
Formato:
- nºpuntos
- X Y */
void creaPuntos(int puntos, string fichero){
    int numX, numY;
    srand(time(NULL));
    ofstream file;
    file.open(fichero.c_str());
    file<<puntos<<"\n";
    for(int c = 1; c <= puntos; c++){
   
        numX = 1 + rand() % (101 - 1);
        numY = 1 + rand() % (101 - 1);
        file<< numX<< " "<<numY<<"\n";
        
    }
  file.close();
}
/*
Devuelve los puntos X.
Pasamos el fichero a leer y la array a llenar.
*/
int *getX(string fichero, int* x){
    ifstream fe(fichero.c_str());
    int aux, tam;
    fe >>tam;
    int cont = 0;
    while(cont < tam) {
        fe >>aux;
        x[cont]= aux;
        //cout<<"X--> "<<aux<<endl;

        fe >>aux;
        cont++;
    }
    fe.close();
    return x;
}
/*
Devuelve los puntos Y.
Pasamos el fichero a leer y la array a llenar.
*/
int *getY(string fichero, int* y){
    ifstream fe(fichero.c_str());
    int aux, tam;
    fe >>tam;
    int cont = 0;
    while(cont < tam) {
        fe >>aux;
        fe >>aux;

        y[cont]= aux;
        //cout<<"Y--> "<<aux<<endl;

        cont++;
    }
    fe.close();
    return y;
}
/*
Devuelve el total de puntos.
Pasamos el fichero.
*/
int total(string fichero){
    ifstream fe(fichero.c_str());
    int aux;
    fe >>aux;
    fe.close();
    return aux;
}
 
//ecuacion de la recta: y = a + bx;
//pendiente de la recta: b
//punto de intercepción en la ordenada: a

void regression(int auxX[], int auxY[],int numPuntos,double &a, double &b){
     double sumY=0;
     double sumX=0;
     double sumXY=0;
     double sumXCuadrado=0;
     


    for(long int i=0; i<numPuntos; i++){
        sumX+=auxX[i];
        sumY+=auxY[i];
        sumXY = sumXY + auxX[i]*auxY[i];
        sumXCuadrado += auxX[i]*auxX[i];
        
    }
     a = ((  sumY * sumXCuadrado  - sumX*sumXY) /
                            ( numPuntos*sumXCuadrado- sumX*sumX));


    //calculo de la pendiente
     b = (( numPuntos*sumXY - sumX * sumY) /
                            ( numPuntos * sumXCuadrado - sumX*sumX));

    
    //cálculo de la pendiente y el punto de intercepción correcto



}

void plotLine(double &a, double &b, int tamano, int auxX[], int auxY[]){
    ofstream file ("regresion.dat");

    ostringstream sstream;
    sstream << a;
    string cad1 = sstream.str();   

    ostringstream sstream2;
    sstream << b;
    string cad2 = sstream.str(); 
     /*
    string n = to_string(a);
    string m = to_string(b);
    */
    file << "set terminal png size 1000, 1000 enhanced font 'Verdana,10' \n";
    file << "set output \"data.png\"";
    file << "\n";
    file << "set xrange[0:100] \n"; 
    file << "set yrange[0:100] \n";
    string func = "f(x)= ";
    func+=cad2;
    func+="*x";
    //func+=cad1;
    func+="\n";
    file << func;
    file << "plot f(x), '-' with points \n";
    for(int i=0; i<tamano;i++){
    	stringstream ss1;
    	int temp1 = auxX[i];
    	ss1 << temp1;
    	string cad3;
    	ss1 >> cad3;
    	//string aux = to_string(auxX[i]);
    	file << cad3;
    	file << " ";
    	stringstream ss2;
    	int temp2 = auxY[i];
    	ss1 << temp2;
    	string cad4;
    	ss2 >> cad4;
    	//aux = to_string(auxY[i]);
    	file << cad4;
    	file << "\n";
    }


}

int main(int argc, char *argv[])
{
    if(argc < 2){
    	cout << "Error en los argumentos" << endl;
    	return 0;
    }
   
    clock_t start, end;
   // string filename = "muyAlta.in";
    //creaPuntos(1000000, filename);//LLAMA AL METODO PARA CREAR ARCHIVOS DE DISTINTOS TAMAÑO

    string archivo = argv[1];
    int tamano = total(archivo);
   
    int auxX[tamano]; 
    int *x = getX(archivo, auxX);
    //cout<<x[0]<<endl;
    int auxY[tamano]; 
    int *y = getY(archivo, auxY);
    //cout<<y[0]<<endl;

    //pendiente e intercepcion con la ordenada
    double a=0, b=0;
    

    start=clock();
    regression(auxX, auxY,tamano, a, b);
    end = clock();

    double tiempo = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Tiempo: " << fixed << tiempo << setprecision(10) << endl;


    cout << "Ecuación de la recta: y= " << b << "x + " << a << endl;
  
    cout << "Consultar data.png para visualizar la recta" << endl;

    plotLine(a,b,tamano,auxX,auxY);
    system("gnuplot regresion.dat");

    return 0;
    
}
