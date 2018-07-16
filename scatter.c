/*    Objective           : To Scatter an integer array of size "n by 1"        
                          using MPI Collective communication library call 
                          (MPI_Scatter)
*******************************************************************
*/



#include <stdio.h>
#include "mpi.h"

main(int argc, char** argv) 
{

  /* Initialization */
  int        numproc, MyRank, root = 0;
  int        *input, *recv_data;
  int        scatter_size; 
  int        index, data_size;
  FILE       *fp;
  MPI_Status status;     

  /* MPI */
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
  MPI_Comm_size(MPI_COMM_WORLD, &numproc);

  if(MyRank == root) {

    /* Read */

    if ((fp = fopen ("data.txt", "r")) == NULL)
    {
       printf("\nCan't open input file");
       exit(-1);
    }

    fscanf(fp, "%d\n", &data_size);     


    input = (int *)malloc(data_size * sizeof(int));

    for(index=0; index< data_size; index++) 
        fscanf(fp, "%d", &input[index]);     
  }	
  // Using Bcast to cast the datasize to all processors

  MPI_Bcast(&data_size, 1, MPI_INT, root, MPI_COMM_WORLD);
  if(data_size % numproc != 0) { 
     if(MyRank == root)
        printf("Input not divisible by Numprocs\n");
     MPI_Finalize();
     exit(-1);
  }

  scatter_size = data_size / numproc;
  recv_data= (int *)malloc(scatter_size * sizeof(int));

  MPI_Scatter(input, scatter_size, MPI_INT, recv_data, 
	      scatter_size, MPI_INT, root, MPI_COMM_WORLD); 

  for(index = 0; index < scatter_size; ++index)
      printf("MyRank = %d, recv_data[%d] = %d \n", 
	      MyRank, index, recv_data[index]);

 MPI_Finalize();

}




