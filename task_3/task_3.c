#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc , char** argv)
{
	int size = 0;
	int rank = 0;
	int i = 0;
	int start = 0;
	int* arr = NULL;
	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	arr = (int*)calloc(size , sizeof(int));
	if ((rank == 0) && (start == 0))
	{
		for (i = 0 ; i < size ; ++i)
		{
			arr[i] = i;
			printf("arr[%d] = %d\n" , i , arr[i]);
		}
		printf("rank = %d , arr[%d] = %d\n" , rank , rank , arr[rank]);
		if (rank + 1 > size - 1)
			MPI_Send(arr , size , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
		else
			MPI_Send(arr , size , MPI_INT , rank + 1 , 0 , MPI_COMM_WORLD);
	}
	else
	{
		if (rank == 0)
		{
			MPI_Recv(arr , size , MPI_INT , size - 1 , 0 , MPI_COMM_WORLD , NULL);
			for (i = 0 ; i < size ; ++i)
			{
				printf("arr[%d] = %d\n" , i , arr[i]);
			}
			printf("rank = %d , arr[%d] = %d\n" , rank , rank , arr[rank]);
			if (rank + 1 > size - 1)
				MPI_Send(arr , size , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
			else
				MPI_Send(arr , size , MPI_INT , rank + 1 , 0 , MPI_COMM_WORLD);
		}
		else
		{
			MPI_Recv(arr , size , MPI_INT , rank - 1 , 0 , MPI_COMM_WORLD , NULL);
			for (i = 0 ; i < size ; ++i)
			{
				printf("arr[%d] = %d\n" , i , arr[i]);
			}
			printf("rank = %d , arr[%d] = %d\n" , rank , rank , arr[rank]);
			if (rank + 1 > size - 1)
				MPI_Send(arr , size , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
			else
				MPI_Send(arr , size , MPI_INT , rank + 1 , 0 , MPI_COMM_WORLD);
		}
	}
	
	free(arr);
	MPI_Finalize();
	return 0;
}
