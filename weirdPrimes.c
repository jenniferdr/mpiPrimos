#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char** argv){
  int myid, numProc;
    
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);

  if(myid==0){

    char str_p[4];
    /*Pedir la entrada*/
    scanf ("%s",str_p); /*Cantidad de numeros primos*/
    int p= atoi(str_p);
    
    /*Formar un arreglo con la primera mitad de los numeros*/
    /*Formar un arreglo con la segunda mitad*/
    /*Pasarle a cada hijo lo que debe hacer*/
  }
    /*Debemos recibir lo que nos mando el proceso 0 y verificar */
 
  if(myid==0){
    /*Recibir todas las respuestas y ordenarlas de menor a mayor para imprimir*/
  }

  /*Todo el programa*/

  MPI_Finalize();
  return 0;

}
