#include <stdlib.h>
#include "iterator.h"

iterator *iterator_create(CommonList *data) {
	iterator *iter;
	if((iter = malloc(sizeof(*iter))) == NULL)
		return NULL;
	iter->next = data->head;
	return iter;
}

void iterator_release(iterator *iter) {
	free(iter);
}

Node *iterator_next(iterator *iter) {
	Node *node = iter->next;
	if(node != NULL)
		iter->next = node->next;
	return node;
}

void iterator_rewind(CommonList *data, iterator *iter) {
	iter->next = data->head;
}