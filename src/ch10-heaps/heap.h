#ifndef HEAP_H
#define HEAP_H
typedef struct Heap_ {
  int size;
  void **data;
  int (*cmp)(const void *, const void *);
  void (*destroy)(void *data);
} Heap;

#define heap_size(h) ((h)->size)

int heap_init(Heap *h, int (*cmp)(const void *, const void *),
              void (*destroy)(void *));

int heap_insert(Heap *h, void *data);
int heap_extract(Heap *h, void **out);
void heap_destroy(Heap *h);
#endif
