#include <stdio.h>
#include "mpi.h"

int main(int argc , char** argv)
{
	int rank = 0;
	int comm = 0;
	MPI_Init(&argc , &argv);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	MPI_Comm_size(MPI_COMM_WORLD , &comm);
	printf("Comm_size = %d\n rank = %d\n" , comm , rank);
	MPI_Finalize();
	return 0;
} 
