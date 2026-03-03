#include "heap.h"
#include <stdlib.h>
#include <string.h>

#define heap_parent(npos) ((npos - 1) / 2)
#define heap_left(npos) ((npos * 2) + 1)
#define heap_right(npos) ((npos * 2) + 2)

int heap_init(Heap *h, int (*cmp)(const void *, const void *),
              void (*destroy)(void *)) {

  memset(h, 0, sizeof(Heap));
  h->cmp = cmp;
  h->destroy = destroy;

  return 0;
}

int heap_insert(Heap *h, void *data) {
  void *temp;
  if ((temp = realloc(h->data, (heap_size(h) + 1) * sizeof(void *))) == NULL)
    return -1;

  h->data = temp;

  int ipos = heap_size(h);
  int ppos = heap_parent(ipos);
  h->data[ipos] = data;

  while (ipos > 0 && h->cmp(h->data[ppos], h->data[ipos]) < 0) {
    void *temp = h->data[ppos];
    h->data[ppos] = h->data[ipos];
    h->data[ipos] = temp;

    ipos = ppos;
    ppos = heap_parent(ipos);
  }

  h->size += 1;
  return 0;
}

void heap_destroy(Heap *h) {
  for (int i = 0; i < heap_size(h); i++) {
    if (h->destroy)
      h->destroy(h->data[i]);
  }
  free(h->data);
  memset(h, 0, sizeof(Heap));
}

int heap_extract(Heap *h, void **out) {
  if (heap_size(h) == 0)
    return -1;

  h->size -= 1;
  *out = h->data[0];

  if (h->size > 0) {
    void *temp;
    void *last = h->data[heap_size(h)];

    if ((temp = realloc(h->data, h->size * sizeof(void *))) == NULL)
      return -1;

    int current_pos = 0;
    int next_pos = 0;
    int left_pos = heap_left(next_pos);
    int right_pos = heap_right(next_pos);

    if (h->cmp(h->data[left_pos], h->data[next_pos]) > 0)
      next_pos = left_pos;

    if (h->cmp(h->data[right_pos], h->data[current_pos]) > 0)
      next_pos = right_pos;

    h->data = temp;
    h->data[0] = last;
  } else {
    free(h->data);
    h->data = NULL;
  }

  return 0;
}
