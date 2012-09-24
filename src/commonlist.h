#ifndef __COMMON_H__
#define __COMMON_H__

typedef struct Node
{
	struct Node *prev;
	struct Node *next;
	void *value;
} Node;

typedef struct CommonList
{
	Node *head;
	Node *tail;
	unsigned long size;
	void (*free)(void *ptr);
} CommonList;

#endif