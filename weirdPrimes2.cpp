#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<string>
#include <math.h>
#include <mpi.h>

using namespace std;

bool esPrimo(int numero){
  int cont = 2;
  int numero1= sqrt(numero);
  
  //printf("raiz %d, ",numero1);
  if (numero == 1){
    return true;
  } 
  while(numero1>= cont){
    if (numero%cont==0){
      return false;
    } 
    cont++;
  }
  if (numero1< cont){
    return true;
  }
}

int main(int argc,char** argv){
  int myid, numProc;

  MPI_Init(&argc,&argv);

  // Todos leen la entrada 
  string cadena;

  ifstream fe;
  fe.open(argv[1],ios::in);
  
  fe >> cadena;
  int N=atoi(cadena.c_str());

  string firstHalves[N];
  string secondHalves[N];

  for(int i=0; i<N ; i++){
    fe >> firstHalves[i];
  }
  for(int i=0; i<N; i++){
    fe >> secondHalves[i];
  }

  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);
  
  int base= N/numProc;

 
  // Cada proceso verifica los numeros q le toca
  for(int i=myid*base; i<myid*base+base ; i++){
    printf("[%d , %d)",i,myid*base+base);
    for(int j=0; j<N ; j++){
      printf("Los j: %d  ",j);
      
      string strNumero;
      strNumero= firstHalves[i];
      strNumero.append(secondHalves[j]);
      int numero= atoi(strNumero.c_str());
      if(esPrimo(numero)){
	printf("%d \n",numero);
      }

    // Encargarse de el resto
    }
  }

  MPI_Finalize();
  return 0;

}
