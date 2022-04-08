#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc , char** argv)
{
	int rank = 0;
	int size = 0;
	int N = 0;
	int summ = 0;
	int i = 0;
	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	N = strtol(argv[1] , NULL , 10);
	int piece = N / size;
	for (i = 0 ; i < piece ; ++i)
	{
		summ +=  (piece * rank + i);
	}
	if (rank == 0)
	{
		int rest = N % size;
		for (i = 0 ; i <= rest ; ++i)
		{
			summ += N - rest + i;
		}
		int per = 0;
		for (i = 1 ; i < size ; ++i)
		{	
			MPI_Recv(&per , 1 , MPI_INT , i , 0 , MPI_COMM_WORLD , NULL);
			summ += per;
		}
		printf("result = %d\n" , summ);
	}
	else
	{
		MPI_Send(&summ , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
