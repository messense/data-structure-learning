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
	Node *current, *next;
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

void *stack_pop(stack *stack) {
	if(stack->size == 0)
		return NULL;
	Node *node, *next;
	node = stack->head;
	next = node->next;
	node->next = NULL;
	stack->head = next;
	stack->size--;
	return node->value;
}

stack *stack_push(stack *stack, void *value) {
	Node *node;
	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(stack->size == 0) {
		stack->head = stack->tail = node;
	} else {
		Node *current;
		current = stack->head;
		node->next = current;
		stack->head = node;
	}
	stack->size++;
	return stack;
}