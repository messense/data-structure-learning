#include <stdio.h>
#include <stdlib.h>
#include "../src/queue.h"

int main(int argc, char const *argv[])
{
	queue *queue = queue_create();
	if(!queue) {
		printf("Allocate memory error!\n");
		exit(0);
	}
	int num;
	printf("Please input some positive numbers.Stop input with number 0.\n");
	scanf("%d", &num);
	while(num > 0) {
		queue = enqueue(queue, (void *)num);
		scanf("%d", &num);
	}
	printf("Print the numbers below.\n\n");
	int value;
	while((value = (int)dequeue(queue)) != NULL) {
		printf("%d\n", value);
	}
	queue_release(queue);
	printf("\nEnd printing.\n");
	return 0;
}