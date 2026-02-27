#include "oahash_table.h"
#include <stdlib.h>
#include <string.h>

int oahash_table_init(OAHashTable *t, int table_size,
                      unsigned long (*h1)(const void *),
                      unsigned long (*h2)(const void *),
                      int (*match)(const void *, const void *),
                      void (*destroy)(void *data)) {
  static char vacated;

  t->table_size = table_size;
  t->size = 0;
  t->h1 = h1;
  t->h2 = h2;
  t->match = match;
  t->destroy = destroy;
  t->slots = calloc(table_size, sizeof(void *));
  t->vacated = &vacated;

  return 0;
}

int oahash_table_insert(OAHashTable *t, void *data) {
  if (t->size == t->table_size)
    return 1;

  int start = t->h1(data) % t->table_size;
  int step = 1 + (t->h2(data) % (t->table_size - 1));
  for (int i = 0; i < t->table_size; i += 1) {
    int k = (start + i * step) % t->table_size;
    if (t->slots[k] == NULL || t->slots[k] == t->vacated) {
      t->slots[k] = data;
      t->size += 1;
      return 0;
    } else if (t->match(t->slots[k], data) == 0) {
      return 1;
    }
  }

  return 1;
}

int oahash_table_lookup(const OAHashTable *t, const void *data, void **out) {
  int start = t->h1(data) % t->table_size;
  int step = 1 + (t->h2(data) % (t->table_size - 1));
  for (int i = 0; i < t->table_size; i += 1) {
    int k = (start + i * step) % t->table_size;
    if (t->slots[k] == NULL)
      return 0;

    if (t->slots[k] != t->vacated && t->match(data, t->slots[k]) == 0) {
      *out = t->slots[k];
      return 1;
    }
  }
  return 0;
}

int oahash_table_remove(OAHashTable *t, const void *data, void **out) {
  int start = t->h1(data) % t->table_size;
  int step = 1 + (t->h2(data) % (t->table_size - 1));
  for (int i = 0; i < t->table_size; i += 1) {
    int k = (start + i * step) % t->table_size;
    if (t->slots[k] == NULL)
      return 1;

    if (t->slots[k] != t->vacated && t->match(t->slots[k], data) == 0) {
      *out = t->slots[k];
      t->slots[k] = t->vacated;
      t->size -= 1;
      return 0;
    }
  }
  return 1;
}

void oahash_table_destroy(OAHashTable *t) {
  for (int i = 0; i < t->table_size; ++i) {
    if (t->destroy && t->slots[i] && t->slots[i] != t->vacated)
      t->destroy(t->slots[i]);
  }
  memset(t, 0, sizeof(OAHashTable));
}
