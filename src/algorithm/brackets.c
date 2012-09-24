#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stack.h"

int main(int argc, char const *argv[])
{
	stack *stk = stack_create();
	int str;
	printf("Please input some thing:\n");
	while((str = getchar())) {
		if(str == 40 || str == 123 || str == 91 || str == 60) // (、{、[、<
			stk = stack_push(stk, (void *)str);
		if(str == 41 || str == 125 || str == 93 || str == 62) { // )、}、]、>
			if(stk->size == 0) {
				printf("Error bracket\n");
				exit(0);
			} else {
				Node *node = stack_pop(stk);
				int tp = (int)node->value;
				if((str == 41 && tp == 40) || (str == 125 && tp == 123) || (str == 93 && tp == 91) || (str == 62 && tp == 60)) {
					printf("Great! Right bracket typed.\n");
				} else {
					printf("Error bracket\n");
					//printf("str=%d, tp=%d\n", str, tp);
					exit(0);
				}
				free(node);
			}
		}
	}
	stack_release(stk);
	printf("Exit. Thank you.\n");
	return 0;
}