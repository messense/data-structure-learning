#include <stdlib.h>
#include "queue.h"

queue *queue_create(void) {
	queue *queue;
	if((queue = malloc(sizeof(*queue))) == NULL)
		return NULL;
	queue->head = queue->tail = NULL;
	queue->free = NULL;
	queue->size = 0;
	return queue;
}

void queue_release(queue *queue) {
	unsigned long size = queue->size;
	Node *current, *next;
	current = queue->head;
	while(size--) {
		next = current->next;
		if(queue->free)
			queue->free(current->value);
		free(current);
		current = next;
	}
	free(queue);
}

queue *enqueue(queue *queue, void *value) {
	Node *node;
	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	node->next = NULL;
	if(queue->size == 0) {
		queue->head = queue->tail = node;
	} else {
		queue->tail->next = node;
		queue->tail = node;
	}
	queue->size++;
	return queue;
}

Node *dequeue(queue *queue) {
	if(queue->size == 0)
		return NULL;
	Node *node = queue->head;
	queue->head = node->next;
	node->next = NULL;
	queue->size--;
	return node;
}