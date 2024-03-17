// commands:
// gcc 4_17.c -o thread -lpthread
// ./thread
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variate shraed by the thread(s).
int total_num = 0;  // the total number of points
int cnt_circle = 0;  // count the number of points in circle


// Thread to generate points randomly, and count the number of points in the circle.
void thread(int);

// Main function.
int main(int argc, char *argv[])
{
	srand(time(0));
	
	// Declare a thread.
	pthread_t tid;  // the thread identifier
	pthread_attr_t attr;  // set of attributes for the thread
	pthread_attr_init(&attr);  // Get the default attributes.

	// Generate 100, 200, 300, 400, 500 points seperately, and compare different results.
	for(int i = 0; i < 5; ++i)
	{
		total_num = 100 + i * 100;
		// Create the thread.
		int ret = pthread_create(&tid, &attr, thread, total_num);  // return 0 if created successfully
		if (ret)
		{
			printf("Error in creating pthread\n");
			exit(1);
		}
	
		// Now wait for the thread to exit.
		pthread_join(tid, NULL);

		// Calculate the value of PI.
		printf("The total number of points is %d\n", total_num);
		printf("The number of points in the circle is %d\n",cnt_circle);
		double PI = 4 * cnt_circle / (double)total_num;
		printf("PI = %f\n\n", PI);
	}
	
	return 0;
}

// Thread to generate points randomly, and count the number of points in the circle.
void thread(int total)
{
	cnt_circle = 0;
	for (int i = 0; i < total; ++i)
	{
		double x = rand() / (double)RAND_MAX * 2 - 1;
		//printf("x = %f\n", x);
		double y = rand() / (double)RAND_MAX * 2 - 1;
		//printf("y = %f\n", y);
		if (x * x + y * y <= 1)
			++cnt_circle;
	}
}

