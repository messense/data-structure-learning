#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "commonlist.h"

typedef CommonList queue;

queue *queue_create(void);
void queue_release(queue *queue);
queue *enqueue(queue *queue, void *value);
void *dequeue(queue *queue);

#endif