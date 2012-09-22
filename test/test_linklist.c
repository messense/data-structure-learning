#include <stdio.h>
#include <stdlib.h>
#include "../linklist.h"

int main(int argc, char const *argv[])
{
	list *list = list_create();
	if(!list) {
		printf("Allocate memory error!\n");
		exit(0);
	}
	int num;
	printf("Please input some positive numbers.Stop input with number 0.\n");
	scanf("%d", &num);
	while(num > 0) {
		list = list_add(list, (void *)num);
		scanf("%d", &num);
	}
	printf("Print the numbers below.\n\n");
	listIter *iter = list_get_iterator(list);
	listNode *node;
	while((node = list_next(iter)) != NULL) {
		printf("%d\n", (int)node->value);
	}
	list_release_iterator(iter);
	list_release(list);
	printf("\nEnd printing.\n");
	return 0;
}