// commands:
// gcc 4_16.c -o thread -lpthread
// ./thread
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Data shared by the threads.
const int num = 5;  // define the number of integers.
double avg = 0.0;
int min = 0;
int max = 0;

// Threads to calcuate different values.
void get_avg(int[num]);
void get_min(int[num]);
void get_max(int[num]);

// Main function.
int main(int argc, char *argv[])
{
	// Input.
	printf("Enter %d integers:\n", num);
	int arr[num];
	for (int i = 0; i < num; ++i)
		scanf("%d", &arr[i]);
		
	// Declare a thread.
	pthread_t tid_avg, tid_min, tid_max;  // the thread identifiers
	pthread_attr_t attr;  // set of attributes for the thread
	pthread_attr_init(&attr);  // Get the default attributes.
	
	// Create the thread to calculate the average value.
	int ret_avg = pthread_create(&tid_avg, &attr, get_avg, arr);  // return 0 if created successfully
	if (ret_avg)
	{
		printf("Error in creating pthread: get_avg\n");
		exit(1);
	}	
	// Wait for the thread to exit.
	pthread_join(tid_avg, NULL);
	
	// Create the thread to calculate the minimum value.
	int ret_min = pthread_create(&tid_min, &attr, get_min, arr);  // return 0 if created successfully
	if (ret_min)
	{
		printf("Error in creating pthread: get_min\n");
		exit(1);
	}
	// Wait for the thread to exit.
	pthread_join(tid_min, NULL);
	
	// Create the thread to calculate the minimum value.
	int ret_max = pthread_create(&tid_max, &attr, get_max, arr);  // return 0 if created successfully
	if (ret_max)
	{
		printf("Error in creating pthread: get_max\n");
		exit(1);
	}
	// Wait for the thread to exit.
	pthread_join(tid_max, NULL);
	
	// Print the result.
	printf("The average value is %f\n", avg);
	printf("The minimum value is %d\n", min);
	printf("The maximum value is %d\n", max);
	
	return 0;
}

// Thread to calculate the average value.
void get_avg(int arr[num])
{
	int sum = 0;
	for (int i = 0; i < num; ++i)
		sum += arr[i];
	avg = sum / (double)num;
}

// Thread to calculate the minimum value.
void get_min(int arr[num])
{
	min = arr[0];
	for (int i = 1; i < num; ++i)
		if (min > arr[i])
			min = arr[i];
}

// Thread to calculate the maximum value.
void get_max(int arr[num])
{
	max = arr[0];
	for (int i = 1; i < num; ++i)
		if (max < arr[i])
			max = arr[i];
}
