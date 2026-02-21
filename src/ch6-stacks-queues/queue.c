#include "queue.h"
#include <string.h>

void queue_init(Queue *q, void (*destroy)(void *)) {
  List *list = malloc(sizeof(List));
  list_init(list, destroy);
  q->list = list;
}

void queue_destroy(Queue *q) {
  list_destroy(q->list);
  free(q->list);
  memset(q, 0, sizeof(Queue));
}

int queue_size(const Queue *q) { return q->list->size; }

int queue_peek(const Queue *q, void **data) {
  if (queue_size(q) == 0)
    return -1;

  *data = q->list->head->data;

  return 0;
}

int queue_enqueue(Queue *q, void *data) {
  return list_insert_next(q->list, q->list->tail, data);
}

int queue_dequeue(Queue *q, void **data) {
  if (queue_size(q) == 0)
    return -1;

  list_remove_next(q->list, NULL, data);

  return 0;
}
