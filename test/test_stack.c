#include <stdio.h>
#include <stdlib.h>
#include "../stack.h"

int main(int argc, char const *argv[])
{
	stack *stack = stack_create();
	if(!stack) {
		printf("Allocate memory error!\n");
		exit(0);
	}
	int num;
	printf("Please input some positive numbers.Stop input with number 0.\n");
	scanf("%d", &num);
	while(num > 0) {
		stack = stack_push(stack, (void *)num);
		scanf("%d", &num);
	}
	printf("Print the numbers below.\n\n");
	stackNode *node;
	while((node = stack_pop(stack)) != NULL) {
		printf("%d\n", (int)node->value);
	}
	stack_release(stack);
	printf("\nEnd printing.\n");
	return 0;
}