/* main.c */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <malloc.h>

#include "buffer.h"

int p_id, c_id;
sem_t empty, full;
pthread_mutex_t mutex;

/* threads call these functions */
void* producer();
void* consumer();

int main(int argc, char *argv[])
{
	srand(time(0));
	int i = 0;

	/* get command line arguments */
	int sleep_time = atoi(argv[1]);
	int p_num = atoi(argv[2]);
	int c_num = atoi(argv[3]);
	if (argc != 4)
	{
		fprintf(stderr, "usage: a.out <integer value>\n");
		return -1;
	}
	if (sleep_time < 0 || p_num < 0 || c_num < 0)
	{
		fprintf(stderr, "all 3 arguments must be >= 0\n");
		return -1;
	}
	printf("sleep time: %d, producer number: %d, consumer number: %d\n\n", sleep_time, p_num, c_num);

	/* threads */
	int mutex_lock = pthread_mutex_init(&mutex, NULL);
	pthread_t* p = (pthread_t*)malloc(sizeof(pthread_t) * p_num);
	pthread_t* c = (pthread_t*)malloc(sizeof(pthread_t) * c_num);
	
	/* return value of threads */
	int* p_ret = (int*)malloc(sizeof(int) * p_num);
	int* c_ret = (int*)malloc(sizeof(int) * c_num);

	/* initialize buffer */
	buffer_item temp = 0;
	while (insert_item(temp) != -1);
	buffer[rear] = 0;
	rear = (rear + 1) % BUFFER_SIZE;
	printf("initial ");
	print_buffer();
	
	/* create producer thread(s) */
	for (i = 0; i < p_num; ++i)
	{
		p_ret[i] = pthread_create(&p[i], NULL, producer, NULL);
		if (p_ret[i] != 0)
		{
			printf("failed to create producer_%d\n", i);
			exit(1);
		}
	}
	
	/* create consumer thread(s) */
	for (i = 0; i < c_num; ++i)
	{
		c_ret[i] = pthread_create(&c[i], NULL, consumer, NULL);
		if (c_ret[i] != 0)
		{
			printf("failed to create consumer_%d\n", i);
			exit(1);
		}
	}
	
	/* sleep */
	sleep(sleep_time);
	
	/* exit */
	return 0;
}

void *producer()
{
	int id = ++p_id;
	int ret = sem_init(&empty, 0, BUFFER_SIZE);

	while (true)
	{
		/* sleep for a random period of time */
		int time = rand() % 5;
		sleep(time);

		/* wait */
		sem_wait(&empty);
		sem_getvalue(&empty, &ret);
		pthread_mutex_lock(&mutex);

		/* generate a random number */
		buffer_item item = rand() % 10;
		
		/* insert to buffer */
		if (insert_item(item) == -1)
			fprintf(stderr, "failed to insert\n");
		else
			printf("producer_%d produced %d after sleeping %d\n", id, item, time);
		
		/* signal */
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		
		/* print buffer */
		print_buffer();
	}
}

void *consumer()
{
	int id = ++c_id;
	int ret = sem_init(&empty, 0, BUFFER_SIZE);

	while (true)
	{
		/* sleep for a random period of time */
		int time = rand() % 5;
		sleep(time);

		/* wait */
		sem_wait(&full);
		sem_getvalue(&empty, &ret);
		pthread_mutex_lock(&mutex);
				
		/* remove from buffer */
		buffer_item item = 0;
		if (remove_item(&item) == -1)
			fprintf(stderr, "failed to remove\n");
		else
			printf("consumer_%d consumed %d after sleeping %d\n", id, item, time);
		
		/* signal */
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		
		/* print buffer */
		print_buffer();
	}
}
