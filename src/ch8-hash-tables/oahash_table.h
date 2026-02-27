#ifndef OAHASHTABLE_H
#define OAHASHTABLE_H
typedef struct OAHashTable_ {
  int table_size;
  int size;
  void **slots;
  unsigned long (*h1)(const void *);
  unsigned long (*h2)(const void *);
  int (*match)(const void *, const void *);
  void (*destroy)(void *data);
  void *vacated;
} OAHashTable;

int oahash_table_init(OAHashTable *t, int table_size,
                      unsigned long (*h1)(const void *),
                      unsigned long (*h2)(const void *),
                      int (*match)(const void *, const void *),
                      void (*destroy)(void *data));
int oahash_table_insert(OAHashTable *t, void *data);
int oahash_table_lookup(const OAHashTable *t, const void *data, void **out);
int oahash_table_remove(OAHashTable *t, const void *data, void **out);
void oahash_table_destroy(OAHashTable *t);
#endif
