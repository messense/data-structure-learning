#include <stdlib.h>
#include "adlist.h"

list *list_create(void) {
	struct list *list;
	if((list = malloc(sizeof(*list))) == NULL)
		return NULL;
	list->head = list->tail = NULL;
	list->len = 0;
	list->dup = NULL;
	list->free = NULL;
	list->match = NULL;
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
		node->prev = node->next = NULL;
	} else {
		node->prev = NULL;
		node->next = list->head;
		list->head->prev = node;
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
		node->prev = node->next = NULL;
	} else {
		node->prev = list->tail;
		node->next = NULL;
		list->tail->next = node;
		list->tail = node;
	}
	list->len++;
	return list;
}

list *list_insert(list *list, listNode *old_node, void *value, int after) {
	listNode *node;
	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(after) {
		node->prev = old_node;
		node->next = old_node->next;
		if(list->tail == old_node)
			list->tail = node;
	} else {
		node->next = old_node;
		node->prev = old_node->prev;
		if(list->head == old_node)
			list->head = node;
	}
	if(node->prev != NULL)
		node->prev->next = node;
	if(node->next != NULL)
		node->next->prev = node;
	list->len++;
	return list;
}

void list_remove(list *list, listNode *node) {
	if(node->prev)
		node->prev->next = node->next;
	else
		list->head = node->next;
	if(node->next)
		node->next->prev = node->prev;
	else
		list->tail = node->prev;
	if(list->free)
		list->free(node->value);
	free(node);
	list->len--;
}

listIter *list_get_iterator(list *list, int direction) {
	listIter *iter;
	if((iter = malloc(sizeof(*iter))) == NULL)
		return NULL;
	if(direction == AL_START_HEAD)
		iter->next = list->head;
	else
		iter->next = list->tail;
	iter->direction = direction;
	return iter;
}

void list_release_iterator(listIter *iter) {
	free(iter);
}

void list_rewind(list *list, listIter *iter) {
	iter->next = list->head;
	iter->direction = AL_START_HEAD;
}

void list_rewind_tail(list *list, listIter *iter) {
	iter->next = list->tail;
	iter->direction = AL_START_TAIL;
}

listNode *list_next(listIter *iter) {
	listNode *current = iter->next;
	if(current != NULL) {
		if(iter->direction == AL_START_HEAD)
			iter->next = current->next;
		else
			iter->next = current->prev;
	}
	return current;
}

list *list_dup(list *l) {
	list *copy = NULL;
	listIter *iter = NULL;
	listNode *node = NULL;

	if((copy = list_create()) == NULL)
		return NULL;
	copy->dup = l->dup;
	copy->free = l->free;
	copy->match = l->match;
	iter = list_get_iterator(l, AL_START_HEAD);
	while((node = list_next(iter)) != NULL) {
		void *value;
		if(copy->dup) {
			value = copy->dup(node->value);
			if(value == NULL) {
				list_release(copy);
				list_release_iterator(iter);
				return NULL;
			}
		} else {
			value = node->value;
		}
		if(list_add_tail(copy, value) == NULL) {
			list_release(copy);
			list_release_iterator(iter);
			return NULL;
		}
	}
	list_release_iterator(iter);
	return copy;
}

listNode *list_search_key(list *list, void *key) {
	listIter *iter;
	listNode *node;
	iter = list_get_iterator(list, AL_START_HEAD);
	while((node = list_next(iter)) != NULL) {
		if(list->match(node->value, key)) {
			list_release_iterator(iter);
			return node;
		} else {
			if(key == node->value) {
				list_release_iterator(iter);
				return node;
			}
		}
	}
	list_release_iterator(iter);
	return NULL;
}

listNode *list_index(list *list, long index) {
	listNode *node;
	if(index < 0) {
		index = (-index)-1;
		node = list->tail;
		while(index-- && node)
			node = node->prev;
	} else {
		node = list->head;
		while(index-- && node)
			node = node->next;
	}
	return node;
}

void list_rotate(list *list) {
	listNode *tail = list->tail;
	if(list->len <= 1) return;
	list->tail = tail->prev;
	list->tail->next = NULL;
	list->head->prev = tail;
	tail->prev = NULL;
	tail->next = list->head;
	list->head = tail;
}