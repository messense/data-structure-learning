#include <stdio.h>
#include <stdlib.h>
#include "../src/linklist.h"
#include "../src/iterator.h"

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
	//listIter *iter = list_get_iterator(list);
	iterator *iter = iterator_create(list);
	Node *node;
	while((node = iterator_next(iter)) != NULL) {
		printf("%d\n", (int)node->value);
	}
	iterator_release(iter);
	list_release(list);
	printf("\nEnd printing.\n");
	return 0;
}