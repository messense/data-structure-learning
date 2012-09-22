#ifndef __STACK_H__
#define __STACK_H__

typedef struct stackNode {
	struct stackNode *next;
	void *value;
} stackNode;

typedef struct stack
{
	stackNode *head;
	stackNode *tail;
	unsigned long size;
	void (*free)(void *ptr);
} stack;

typedef struct stackIter
{
	stackNode *next;
} stackIter;

stack *stack_create(void);
void stack_release(stack *stack);
stackNode *stack_pop(stack *stack);
stack *stack_push(stack *stack, void *value);
stackIter *stact_iterator(stack *stack);
stackNode *stack_next(stackIter *iter);
void stack_release_iterator(stackIter *iter);

#endif