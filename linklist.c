#include <stdlib.h>
#include "linklist.h"

list *list_create(void) {
	struct list *list;
	if((list = malloc(sizeof(*list))) == NULL)
		return NULL;
	list->head = list->tail = NULL;
	list->len = 0;
	list->free = NULL;
	return list;
}

void list_release(list *list) {
	unsigned long len;
	listNode *current, *next;

	current = list->head;
	len = list->len;
	while(len--) {
		next = current->next;
		if(list->free)
			list->free(current->value);
		free(current);
		current = next;
	}
	free(list);
}

list *list_add_head(list *list, void *value) {
	listNode *node;
	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(list->len == 0) {
		list->head = list->tail = node;
		node->next = NULL;
	} else {
		node->next = list->head;
		list->head = node;
	}
	list->len++;
	return list;
}

list *list_add_tail(list *list, void *value) {
	listNode *node;
	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(list->len == 0) {
		list->head = list->tail = node;
		node->next = NULL;
	} else {
		list->tail->next = node;
		list->tail = node;
	}
	list->len++;
	return list;
}

list *list_add(list *list, void *value) {
	return list_add_tail(list, value);
}

list *list_insert(list *list, listNode *old_node, void *value, int after) {
	return NULL;
}

list *list_remove(list *list, listNode *node) {
	return NULL;
}

listIter *list_get_iterator(list *list) {
	listIter *iter;
	if((iter = malloc(sizeof(*iter))) == NULL)
		return NULL;
	iter->next = list->head;
	return iter;
}

listNode *list_next(listIter *iter) {
	listNode *current = iter->next;
	if(current != NULL)
		iter->next = current->next;
	return current;
}

void list_release_iterator(listIter *iter) {
	free(iter);
}

listNode *list_index(list *list, long index) {
	listNode *node;
	node = list->head;
	while(index-- && node)
		node = node->next;
	return node;
}

void list_rewind(list *list, listIter *iter) {
	iter->next = list->head;
}