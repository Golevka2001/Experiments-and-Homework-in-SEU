/* bridge.c */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <malloc.h>

int begin_time = 0;
int farmer_id = 0;
sem_t available;
pthread_mutex_t mutex;

/* threads call these functions */
void* south_thread();
void* north_thread();

int main(int argc, char *argv[])
{
	srand(time(0));
	begin_time = time(0);
	sem_init(&available, 0, 1);
	
	/* get command line argument */
	int run_time = atoi(argv[1]);
	if (argc != 2)
	{
		fprintf(stderr, "usage: a.out <integer value>\n");
		return -1;
	}
	if (run_time <= 0)
	{
		fprintf(stderr, "argument must be > 0\n");
		return -1;
	}
	
	/* threads */
	int mutex_lock = pthread_mutex_init(&mutex, NULL);
	pthread_t south_tid, north_tid;
	
	/* create south thread */
	int south_ret = pthread_create(&south_tid, NULL, south_thread, NULL);
	if (south_ret != 0)
	{
		printf("failed to create south_thread\n");
		exit(1);
	}
	
	/* create north thread */
	int north_ret = pthread_create(&north_tid, NULL, north_thread, NULL);
	if (north_ret != 0)
	{
		printf("failed to create north_thread\n");
		exit(1);
	}
	
	/* sleep */
	sleep(run_time);
	
	/* exit */
	return 0;
}

void* south_thread()
{
	while (1)
	{
		sleep(rand() / RAND_MAX);
		
		/* wait */
		sem_wait(&available);
		pthread_mutex_lock(&mutex);
		
		/* cross the bridge */
		int current_time = time(0) - begin_time;
		int cross_time = rand() % 4 + 1;
		sleep(cross_time);
		
		/* signal */
		pthread_mutex_unlock(&mutex);
		sem_post(&available);
		
		printf("at %ds, farmer_%d took %ds to cross the bridge from the south.\n", current_time, farmer_id++, cross_time);
		
		sleep(1);
	}
}

void* north_thread()
{
	while (1)
	{
		sleep(rand() / RAND_MAX);
		
		/* wait */
		sem_wait(&available);
		pthread_mutex_lock(&mutex);
		
		/* cross the bridge */
		int current_time = time(0) - begin_time;
		int cross_time = rand() % 4 + 1;
		sleep(cross_time);
		
		/* signal */
		pthread_mutex_unlock(&mutex);
		sem_post(&available);
		
		printf("at %ds, farmer_%d took %ds to cross the bridge from the north.\n", current_time, farmer_id++, cross_time);
	}
}
