#include <stdlib.h>
#include "stack.h"

stack *stack_create(void) {
	stack *stack;
	if((stack = malloc(sizeof(*stack))) == NULL)
		return NULL;
	stack->head = stack->tail = NULL;
	stack->size = 0;
	stack->free = NULL;
	return stack;
}

void stack_release(stack *stack) {
	unsigned long size;
	stackNode *current, *next;
	current = stack->head;
	size = stack->size;
	while(size--) {
		next = current->next;
		if(stack->free)
			stack->free(current->value);
		free(current);
		current = next;
	}
	free(stack);
}

stackNode *stack_pop(stack *stack) {
	if(stack->size == 0)
		return NULL;
	stackNode *node, *next;
	node = stack->head;
	next = node->next;
	node->next = NULL;
	stack->head = next;
	stack->size--;
	return node;
}

stack *stack_push(stack *stack, void *value) {
	stackNode *node;
	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(stack->size == 0) {
		stack->head = stack->tail = node;
	} else {
		stackNode *current;
		current = stack->head;
		node->next = current;
		stack->head = node;
	}
	stack->size++;
	return stack;
}

stackIter *stact_iterator(stack *stack) {
	stackIter *iter;
	if((iter = malloc(sizeof(*iter))) == NULL)
		return NULL;
	iter->next = stack->head;
	return iter;
}

stackNode *stack_next(stackIter *iter) {
	stackNode *node = iter->next;
	if(node != NULL)
		iter->next = node->next;
	return node;
}

void stack_release_iterator(stackIter *iter) {
	free(iter);
}