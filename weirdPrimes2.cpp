#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<string>
#include <math.h>
#include <list>
#include <mpi.h>

using namespace std;

bool esPrimo(long int numero){
  int cont = 2;
  long int numero1= sqrt(numero);
  
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
    //printf("Primera mitad: %s \n",firstHalves[i].c_str());
  }
  for(int i=0; i<N; i++){
    stream >> secondHalves[i];
    //printf("Primera mitad: %s \n",secondHalves[i].c_str());
  }

  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);
  
  // Cantidad de primos que le corresponde a cada proc
  int base= N/numProc;
  //int resto= N%numProc;
  
  long long int primos[N*N];
  int indice=0;
 
  // Cada proceso verifica los numeros q le toca
  for(int i=myid*base; i<myid*base+base ; i++){
    for(int j=0; j<N ; j++){
      string strNumero= firstHalves[i];
      strNumero.append(secondHalves[j]);
      //printf("El string del primo: %s \n",strNumero.c_str());
      long long int numero= atoll(strNumero.c_str());
      //cout << "Viendo si es primo: "<< numero << "\n";
      if(esPrimo(numero)) {
	primos[indice]=numero;
	//cout << "Es primo: " << numero << " proceso" << myid<< endl;
	indice++;
      }
    }
  }

  // Repartir los numeros restantes 
  for(int i=numProc*base; i<N ;i++){
    if(myid==i%(numProc)){
      for(int j=0; j<N ; j++){
	string strNumero= firstHalves[i];
	strNumero.append(secondHalves[j]);
	long long int numero= atoll(strNumero.c_str());
	if(esPrimo(numero)){
	  primos[indice]=numero;
	  indice++;
	}
      }
    }
  }
  for(int i=indice; i<N*N ; i++){
    primos[i]=0;
  }
  
  long long int *buff;
  if(myid==0){
    buff= (long long int*) malloc(sizeof(long long int)*numProc*N*N);
  }


  MPI_Gather(primos,N*N,MPI_LONG_LONG_INT,buff,N*N,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);

  
  list<long long int> listprimos;
  if(myid==0){
    for(int i=0; i<(N*N*numProc); i++){
      if(buff[i]!=0){
	listprimos.push_back(buff[i]);
      }
    }

    listprimos.sort();
    list<long long int>::iterator i;

    for(i=listprimos.begin(); i!=listprimos.end();i++){
      cout << *i << "\n";
    }
  }

  MPI_Finalize();
  return 0;

}
