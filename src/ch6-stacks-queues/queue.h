#ifndef QUEUE_H
#define QUEUE_H
#include "../ch5-linked-lists/list.h"

typedef struct Queue_ {
  List *list;
} Queue;

void queue_init(Queue *q, void (*destroy)(void *));
void queue_destroy(Queue *q);
int queue_enqueue(Queue *q, void *data);
int queue_dequeue(Queue *q, void **data);
int queue_size(const Queue *q);
int queue_peek(const Queue *q, void **data);
#endif
