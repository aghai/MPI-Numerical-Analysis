#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main (int argc, char* argv[]){

  int i,rank, num_procs,N=50;
  int input[N],input_sum[N],input_mult[N];
  double t0, t1, time;

  MPI_Init(&argc, &argv);	
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);	 
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);	

 /*initialization start timing */
  t0 = MPI_Wtime();
  for(i=0;i<N;i++){
    input[i]=rank +1 ;
  }

/* sum and multiplication */
  MPI_Reduce(input,input_sum,N,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
  MPI_Reduce(input,input_mult,N,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);
  if(rank == 0) {
    for(i=0;i<N;i++) printf("sum: %d\n", input_sum[i]); 
  }
  if(rank == 0) {
    for(i=0;i<N;i++) printf("product: %d\n", input_mult[i]) ; 
  }

/* time calculation */
  t1 = MPI_Wtime();
  time = t1 - t0 ;

  if(rank == 0) {
     printf("Total elapsed time [sec] : %f\n", time); 
  } 


  MPI_Finalize();
  return 0;
}

