#ifndef CHHASHTABLE_H
#define CHHASHTABLE_H
#include "../ch5-linked-lists/list.h"

typedef struct CHHashTable_ {
  int size;
  int buckets;
  int (*match)(const void *, const void *);
  unsigned long (*h)(const char *);
  List *table;
} CHHashTable;

int chhash_table_init(CHHashTable *t, int buckets, void (*destroy)(void *),
                      int (*match)(const void *, const void *),
                      unsigned long (*h)(const char *));

int chhash_table_insert(CHHashTable *t, void *data);
int chhash_table_lookup(const CHHashTable *t, const void *data, void **out);
int chhash_table_remove(CHHashTable *t, const void *data, void **out);

void chhash_table_destroy(CHHashTable *t);
#endif
