#include <stdio.h>
#include <mpi.h>
int main (int argc, char * argv[]){
    char machine_name[MPI_MAX_PROCESSOR_NAME];
    int my_id,n,large_name;
    MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
   MPI_Comm_size(MPI_COMM_WORLD,&n);
    MPI_Get_processor_name(machine_name,&large_name);
    
    int numero = 500249;
    int cont = 2;
    int	numero1= sqrt(numero);
	printf("raiz %d, ",numero1);
    if (numero == 1){
 	printf ("es primo");

    } 
while  (numero1>= cont){
 if (numero%cont==0){
		printf ("no es primo");
	} 
 cont++;
}
 if (numero1< cont){

	printf("es primo");
}
    MPI_Finalize();
    return(0);
}

