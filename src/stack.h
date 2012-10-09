#ifndef __STACK_H__
#define __STACK_H__

#include "commonlist.h"

typedef CommonList stack;

stack *stack_create(void);
void stack_release(stack *stack);
void *stack_pop(stack *stack);
stack *stack_push(stack *stack, void *value);

#endif