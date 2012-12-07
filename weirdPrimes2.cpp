#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<string>
#include <math.h>
#include <list>
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
  ifstream stream;
  stream.open(argv[1],ios::in);
  string line;
  stream >> line;

  // La primera linea indica el nº de primos
  int N=atoi(line.c_str());

  string firstHalves[N];
  string secondHalves[N];

  for(int i=0; i<N ; i++){
    stream >> firstHalves[i];
  }
  for(int i=0; i<N; i++){
    stream >> secondHalves[i];
  }

  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);
  
  // Cantidad de primos que le corresponde a cada proc
  int base= N/numProc;
  int resto= N%numProc;
  
  list<int> primos;
 
  // Cada proceso verifica los numeros q le toca
  for(int i=myid*base; i<myid*base+base ; i++){
    for(int j=0; j<N ; j++){
      string strNumero= firstHalves[i];
      strNumero.append(secondHalves[j]);
      int numero= atoi(strNumero.c_str());
      if(esPrimo(numero)) primos.push_back(numero); 
    }
  }

  // Repartir los numeros restantes 
  for(int i=numProc*base; i<N ;i++){
    if(myid==i%(numProc)){
      for(int j=0; j<N ; j++){
	string strNumero= firstHalves[i];
	strNumero.append(secondHalves[j]);
	int numero= atoi(strNumero.c_str());
	if(esPrimo(numero)) primos.push_back(numero); 
      }
    }
  }
  
  

  if(myid==0){
    // Recibir de todos 
    // ordenar
    // Imprimir en orden 
  }

  MPI_Finalize();
  return 0;

}
