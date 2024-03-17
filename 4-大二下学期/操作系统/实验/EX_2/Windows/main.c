/* main.c */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <malloc.h>

#include "buffer.h"

int p_id, c_id;
HANDLE empty, full;
HANDLE mutex;

/* threads call these functions */
DWORD WINAPI producer();
DWORD WINAPI consumer();

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

	/* create mutex and semaphores */
	mutex = CreateMutex(NULL, FALSE, NULL);
	empty = CreateSemaphore(NULL, 5, 5, NULL);
	full = CreateSemaphore(NULL, 0, 5, NULL);

	/* threads */
	DWORD *p = (DWORD *)malloc(sizeof(DWORD) * p_num);
	DWORD *c = (DWORD *)malloc(sizeof(DWORD) * c_num);

	/* return value of threads */
	HANDLE *p_ret = (HANDLE)malloc(sizeof(HANDLE) * p_num);
	HANDLE *c_ret = (HANDLE)malloc(sizeof(HANDLE) * c_num);

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
		p_ret[i] = CreateThread(NULL, 0, producer, NULL, 0, &p[i]);
		if (p_ret[i] == 0)
		{
			printf("failed to create producer_%d\n", i);
			exit(1);
		}
		CloseHandle(p_ret[i]);
		Sleep(100);
	}

	/* create consumer thread(s) */
	for (i = 0; i < c_num; ++i)
	{
		c_ret[i] = CreateThread(NULL, 0, consumer, NULL, 0, &c[i]);
		if (c_ret[i] == 0)
		{
			printf("failed to create consumer_%d\n", i);
			exit(1);
		}
		CloseHandle(c_ret[i]);
		Sleep(100);
	}

	/* sleep */
	Sleep(sleep_time * 1000);

	/* exit */
	return 0;
}

DWORD WINAPI producer()
{
	int id = ++p_id;

	while (true)
	{
		/* sleep for a random period of time */
		int time = rand() % 5;
		Sleep(time * 1000);

		/* wait */
		WaitForSingleObject(empty, INFINITE);
		WaitForSingleObject(mutex, INFINITE);

		/* generate a random number */
		buffer_item item = rand() % 10;

		/* insert to buffer */
		if (insert_item(item) == -1)
			fprintf(stderr, "failed to insert\n");
		else
			printf("producer_%d produced %d after sleeping %d\n", id, item, time);

		/* signal */
		ReleaseMutex(mutex);
		ReleaseSemaphore(full, 1, NULL);

		/* print buffer */
		print_buffer();
	}
}

DWORD WINAPI consumer()
{
	int id = ++c_id;

	while (true)
	{
		/* sleep for a random period of time */
		int time = rand() % 5;
		Sleep(time * 1000);

		/* wait */
		WaitForSingleObject(full, INFINITE);
		WaitForSingleObject(mutex, INFINITE);

		/* remove from buffer */
		buffer_item item = 0;
		if (remove_item(&item) == -1)
			fprintf(stderr, "failed to remove\n");
		else
			printf("consumer_%d consumed %d after sleeping %d\n", id, item, time);

		/* signal */
		ReleaseMutex(mutex);
		ReleaseSemaphore(empty, 1, NULL);

		/* print buffer */
		print_buffer();
	}
}
