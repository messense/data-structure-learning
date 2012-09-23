#include <stdlib.h>
#include "linklist.h"

list *list_create(void) {
	list *list;
	if((list = malloc(sizeof(*list))) == NULL)
		return NULL;
	list->head = list->tail = NULL;
	list->size = 0;
	list->free = NULL;
	return list;
}

void list_release(list *list) {
	unsigned long size;
	Node *current, *next;

	current = list->head;
	size = list->size;
	while(size--) {
		next = current->next;
		if(list->free)
			list->free(current->value);
		free(current);
		current = next;
	}
	free(list);
}

list *list_add_head(list *list, void *value) {
	Node *node;
	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(list->size == 0) {
		list->head = list->tail = node;
		node->next = NULL;
	} else {
		node->next = list->head;
		list->head = node;
	}
	list->size++;
	return list;
}

list *list_add_tail(list *list, void *value) {
	Node *node;
	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(list->size == 0) {
		list->head = list->tail = node;
		node->next = NULL;
	} else {
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
	return list;
}

list *list_add(list *list, void *value) {
	return list_add_tail(list, value);
}

list *list_insert(list *list, Node *old_node, void *value, int after) {
	return NULL;
}

list *list_remove(list *list, Node *node) {
	return NULL;
}

Node *list_index(list *list, long index) {
	Node *node;
	node = list->head;
	while(index-- && node)
		node = node->next;
	return node;
}