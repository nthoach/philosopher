
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread1()
{
	int i;
	for (i=0; i < 10; i++)
	{
		printf("Thread 1: %i\n", i+1);
		sleep (1);
	}
}
void *thread2()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		printf("Thread 2, %i \n", i+1);
		sleep(1);
	}
}

int main(void)
{
	pthread_t th1, th2;
	pthread_create(&th1, NULL, thread1, NULL);
	pthread_create(&th2, NULL, thread2, NULL);
	sleep(20);
	return (0);
}
