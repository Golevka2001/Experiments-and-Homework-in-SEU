/* buffer.h */

typedef int buffer_item;

#define BUFFER_SIZE 5

/* the buffer */
buffer_item buffer[BUFFER_SIZE];

/* pointers of the buffer */
int front = 0, rear = 0;

void print_buffer()
{
	printf("buffer: ");
	int i = 0;
	if (front == rear)
		printf("empty");
	else
		for (i = front; i != rear; i = (i + 1) % BUFFER_SIZE)
			printf("%d\t", buffer[i]);
	printf("\n\n");
}

int insert_item(buffer_item item)
{
	/* if the queue is full, return -1 */
	if((rear + 1) % BUFFER_SIZE == front)
		return -1;
	
	/* insert item into buffer, return 0 */
	buffer[rear] = item;
	rear = (rear + 1) % BUFFER_SIZE;
	return 0;
}

int remove_item(buffer_item *item)
{
	/* if the queue is empty, return -1 */
	if (front == rear)
		return -1;
	
	/* remove an object from buffer and place it in item, return 0 */
	*item = buffer[front];
	front = (front + 1) % BUFFER_SIZE;
	return 0;
}
