#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct queueNode
{
	struct queueNode *next;
	void *value;
} queueNode;

typedef struct queue
{
	queueNode *head;
	queueNode *tail;
	unsigned long size;
	void (*free)(void *ptr);
} queue;

queue *queue_create(void);
void queue_release(queue *queue);
queue *enqueue(queue *queue, void *value);
queueNode *dequeue(queue *queue);

#endif