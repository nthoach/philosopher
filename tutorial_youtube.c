#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>



int	main(void)
{
	pthread_t tid0;
	pthread_create(&tid0, NULL, WorkerThreadFunc, (void *) &tid0);
	pthread_exit(NULL);

}