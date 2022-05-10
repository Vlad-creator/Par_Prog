#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

void* func(void* num);

int main(int argc , char* argv[])
{
	assert(argc == 2);
	char* end = NULL;
	int nthreads = strtol(argv[1], &end, 10);
	int i = 0;
	pthread_t threads[nthreads];
	int args[nthreads];
	for (i = 0 ; i < nthreads ; ++i)
	{
		args[i] = i;
	}
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for (i = 0 ; i < nthreads ; ++i)
	{
		pthread_create(&threads[i] , &attr , func , (void*)(args + i));
	}
	for (i = 0 ; i < nthreads ; ++i)
	{
		pthread_join(threads[i] , NULL);
	}
	return 0;
}

void* func(void* num)
{
	int count = *((int*)(num));
	printf("Hello World\n %d \n\n" , count);
	pthread_exit(0);
}