#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

typedef struct args
{
	int num;
	int count;
	int result;
}args;

void* func(void* num);

int main(int argc , char* argv[])
{
	assert(argc == 3);
	char* end = NULL;
	int nthreads = strtol(argv[1], &end, 10);
	int N = strtol(argv[2], &end, 10);
	int i = 0;
	pthread_t threads[nthreads];
	args args_t[nthreads];
	int diag = N / nthreads;
	for (i = 0 ; i < nthreads ; ++i)
	{
		args_t[i].num = i;
		args_t[i].count = diag;
		args_t[i].result = 0;
	}
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for (i = 0 ; i < nthreads ; ++i)
	{
		pthread_create(&threads[i] , &attr , func , (void*)(args_t + i));
	}
	for (i = 0 ; i < nthreads ; ++i)
	{
		pthread_join(threads[i] , NULL);
	}
	int sum = 0;
	for (i = 0 ; i <= N % nthreads ; ++i)
	{
		sum += (N - i);
	}
	for (i = 0 ; i < nthreads ; ++i)
	{
		sum += args_t[i].result;
	}
	printf("%d\n" , sum);
	return 0;
}

void* func(void* args_t)
{
	args* results = (args*)(args_t);
	int i = results->num * results->count;
	for ( ; i < (results->num + 1) * results->count ; ++i)
	{
		results->result += i;
	}
	//printf("%d\n" , results.count);
	//printf("%d\n" , results.num);
	//printf("%d\n" , results.result);
	pthread_exit(0);
}