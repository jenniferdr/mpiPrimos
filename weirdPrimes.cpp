#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<string>
#include <mpi.h>

using std::string;
using namespace std;

int main(int argc,char** argv){
  int myid, numProc;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);

  if(myid==0){
    char str_p[4];
    /*Pedir la entrada*/
    printf("Introduzca la cantidad de numeros primos que el cientifico raro desordeno:");
    fflush(stdout);
    scanf ("%s",str_p); /*Cantidad de numeros primos*/
    int p= atoi(str_p);
    
    /*Arreglo de las primeras mitades de los numeros*/
    std::string firstHalves[p];
  
    printf("Introduzca la primera mitad de cada numero: \n");
    for(int i=0; i<p ; i++){
      cin >> firstHalves[i];
    }

    printf("Introduzca la segunda mitad de cada numero: \n");
    std::string secondHalves[p];
    for(int i=0; i<p ; i++){
      cin >> secondHalves[i];
    }
    int base = p/numProc;
    int resto = p % numProc;
    
    int N= p+base+resto+1;
    string envio[N];

    envio[0]= to_string(base);
    int i=1;
    int j=0;
 
    for (;i<=base;i++){
      envio[i]=firstHalves[j];
      j++;
    }
    for (int k=0;k<p;k++){
      envio[i]=secondHalves[k];
    }
    MPI_Send(&envio[0],N, MPI_, destino, tag, MPI_COMM_WORLD);
  }


  
  /*Debemos recibir lo que nos mando el proceso 0 y verificar */
 
  if(myid==0){
    /*Recibir todas las respuestas y ordenarlas de menor a mayor para imprimir*/
  }

  /*Todo el programa*/

  MPI_Finalize();
  return 0;

}
