#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "linkedlist.h"

/* function prototypes to be used */
void fill_list(int *);
void empty_list(int *);
void show_list();

/* list */
NODE * headptr;
NODE head;

/* mutex to protect access to list */
pthread_mutuex_t list_mutex;

/* semaphores to synchronize fill_list and empty_list threads */
unsigned int threads_fill_done;
sem_t done_filling_list;
sem_t filling_list;

int main(void)
{
	int	i;

	headptr = &head;
	headptr->next  = NULL;

	pthread_mutex_init(&list_mutex, NULL);
	int res = sem_init(&done_filling_list, 0, 0);
	if (res < 0)
	{
		perror("Semaphore initialization failed");
		exit(0);
	}
	threads_fill_done = 0;
	pthread_t threads[11];
	int param[5] = {0, 1, 2, 3, 4};
	for (i = 0; i < 5; i++)
	{
		pthread_create(&threads[i],
						NULL,
						(void *)empty_list,
						(void *)&param[i-5]);
	}
	for (i = 0; i < 10; i++)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&list_mutex);
	sem_destroy(&filling_list);
	sem_destroy(&done_filling_list);
	printf("All threads completed. List:\n");
	Traverse(headptr);
	return 0;
}



