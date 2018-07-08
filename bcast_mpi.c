//one process will read data from the user, either by reading from the terminal or command line arguments, and then distribute to all other processes.

#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, value;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //one process will read the data

    do{
	if (rank == 0)
	    scanf("%d", &value);
	//Using MPI_Bcast to share the information with all the processes
	//Look up syntax on www.mpich.org

	MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Process %d got %d\n", rank, value);
    }while (value >= 0);
    MPI_Finalize();
    return 0;

}
