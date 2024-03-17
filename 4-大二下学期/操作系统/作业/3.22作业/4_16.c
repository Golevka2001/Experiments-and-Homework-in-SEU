#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
	/* Array. */
	const int arr[8] = {8, 90, 81, 78, 95, 79, 72, 85};  // arr[0] is the size of this array
	
	/* Result. */
	double avg = 0.0;
	int min = 0;
	int max = 0;
	
	/* Process ID. */
	pid_t fpid_1;
	pid_t fpid_2;
	pid_t fpid_3;
	
	/* Create child process 1. */
	fpid_1 = fork();
	if(fpid_1 < 0)  // error
		printf("Error in child process 1\n");
	else if(fpid_1 == 0)  // child process 1
	{
		/* Calculate the average value. */
		double sum = 0;
		for(int i=1; i<arr[0]; i++)
			sum += arr[i];
		avg = sum / (arr[0] - 1);
		
		printf("%d: Child process 1, whose parent process is %d\n", getpid(), getppid());
	}
	else  // parent process
	{
		/* Create child process 2. */
		fpid_2 = fork();
		if(fpid_2 < 0)  // error
			printf("Error in child process 2\n");
		else if(fpid_2 == 0)  // child process 2
		{
			/* Calculate the minimum value. */
			min = arr[1];
			for(int i=2; i<arr[0]; i++)
				if(min > arr[i])
					min = arr[i];
				
			printf("%d: Child process 2, whose parent process is %d\n", getpid(), getppid());
		}
		else  // parent process
		{
			/* Create child process 3. */
			fpid_3 = fork();
			if(fpid_3 < 0)  // error
				printf("Error in child process 3\n");
			else if(fpid_3 == 0)  // child process 3
			{
				/* Calculate the maximum value. */
				max = arr[1];
				for(int i=2; i<arr[0]; i++)
					if(max < arr[i])
						max = arr[i];
				
				printf("%d: Child process 3, whose parent process is %d\n", getpid(), getppid());
			}
			else  // parent process
				printf("\n%d: Parent process, whose child processes are %d, %d, %d\n", getpid(), fpid_1, fpid_2, fpid_3);
		}
	}
	
	/* Print the result in each process(totally 4 times: parent, child_1, child_2, child_3). */
	/* In one process, only one value is calculated, so that the other two values are 0. */
	/* And in the parent process, all the values are 0, for they are calculated in child processes. */
	printf("The average value is %f\n", avg);
	printf("The minimum value is %d\n", min);
	printf("The maximum value is %d\n\n", max);
	
	sleep(1);
	return 0;
}
