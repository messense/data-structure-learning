#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include "commonlist.h"

typedef struct iterator
{
	Node *next;
} iterator;

iterator *iterator_create(CommonList *data);
void iterator_release(iterator *iter);
Node *iterator_next(iterator *iter);
void iterator_rewind(CommonList *data,iterator *iter);

#endif