#include "chhash_table.h"
#include <stdio.h>
#include <string.h>

int chhash_table_init(CHHashTable *t, int buckets, void (*destroy)(void *),
                      int (*match)(const void *, const void *),
                      unsigned long (*h)(const char *)) {
  if ((t->table = malloc(buckets * sizeof(List))) == NULL)
    return -1;

  t->size = 0;
  t->buckets = buckets;
  t->h = h;
  t->match = match;

  for (int i = 0; i < buckets; i++) {
    list_init(&t->table[i], destroy);
  }

  return 0;
}

int chhash_table_insert(CHHashTable *t, void *data) {
  const int k = t->h((const char *)data) % t->buckets;
  List *bucket = &t->table[k];

  void *out;
  if (chhash_table_lookup(t, data, &out) == 1)
    return 1;

  list_insert_next(bucket, bucket->tail, data);
  t->size += 1;
  return 0;
}

int chhash_table_lookup(const CHHashTable *t, const void *data, void **out) {
  const int k = t->h(data) % t->buckets;
  const List bucket = t->table[k];
  for (ListElement *e = bucket.head; e != NULL; e = e->next) {
    if (t->match(data, e->data) == 0) {
      *out = e->data;
      return 1;
    }
  }
  return 0;
}

int chhash_table_remove(CHHashTable *t, const void *data, void **out) {
  ListElement *e, *previous = NULL;
  const int k = t->h(data) % t->buckets;
  List *bucket = &t->table[k];
  for (e = bucket->head; e != NULL; e = e->next) {
    if (t->match(data, e->data) == 0)
      break;

    previous = e;
  }

  if (e == NULL)
    return 1;

  t->size -= 1;
  return list_remove_next(bucket, previous, out);
}

void chhash_table_destroy(CHHashTable *t) {
  for (int i = 0; i < t->buckets; i++) {
    list_destroy(&t->table[i]);
  }
  free(t->table);
  memset(t, 0, sizeof(CHHashTable));
}
