#include "../test_helpers.h"
#include "djb2.h"
#include "h2.h"
#include "oahash_table.h"
#include <stdlib.h>
#include <string.h>

TEST(test_init) {
  OAHashTable t;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  free),
                0);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_INT_EQ(t.table_size, 5);
  ASSERT_PTR_EQ((void *)t.h1, (void *)djb2);
  ASSERT_PTR_EQ((void *)t.h2, (void *)h2);
  ASSERT_PTR_EQ((void *)t.match, (void *)strcmp);
  ASSERT_PTR_EQ((void *)t.destroy, (void *)free);
  ASSERT_PTR_NOT_NULL(t.slots);

  oahash_table_destroy(&t);
}

TEST(test_insert) {
  OAHashTable t;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, "a"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "b"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "c"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "d"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "e"), 0);

  ASSERT_INT_EQ(t.size, 5);

  oahash_table_destroy(&t);
}

TEST(test_insert_duplicate) {
  OAHashTable t;
  void *a = "a";

  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, a), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "a"), 1);
  ASSERT_INT_EQ(t.size, 1);

  oahash_table_destroy(&t);
}

TEST(test_insert_collide) {
  OAHashTable t;
  void *a = "a";
  void *f = "f";
  void *outa = NULL;
  void *outf = NULL;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, a), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, f), 0);

  ASSERT_INT_EQ(t.size, 2);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "a", &outa), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "f", &outf), 1);
  ASSERT_PTR_EQ(a, outa);
  ASSERT_PTR_EQ(f, outf);

  oahash_table_destroy(&t);
}

TEST(test_insert_multi_collide) {
  OAHashTable t;
  void *a = "a";
  void *f = "f";
  void *k = "k";
  void *p = "p";
  void *z = "z";
  void *outa = NULL;
  void *outf = NULL;
  void *outk = NULL;
  void *outp = NULL;
  void *outz = NULL;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, a), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, f), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, k), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, p), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, z), 0);

  ASSERT_INT_EQ(t.size, 5);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "a", &outa), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "f", &outf), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "k", &outk), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "p", &outp), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "z", &outz), 1);

  ASSERT_PTR_EQ(a, outa);
  ASSERT_PTR_EQ(f, outf);
  ASSERT_PTR_EQ(k, outk);
  ASSERT_PTR_EQ(p, outp);
  ASSERT_PTR_EQ(z, outz);

  oahash_table_destroy(&t);
}

TEST(test_reinsert) {
  OAHashTable t;
  void *a = "a";
  void *b = "b";
  void *c = "c";
  void *d = "d";
  void *e = "e";
  void *out = NULL;
  void *outa = NULL;
  void *outb = NULL;
  void *outc = NULL;
  void *outd = NULL;
  void *oute = NULL;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, a), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, b), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, c), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, d), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, e), 0);

  ASSERT_INT_EQ(oahash_table_remove(&t, "a", &out), 0);
  ASSERT_INT_EQ(oahash_table_remove(&t, "b", &out), 0);
  ASSERT_INT_EQ(oahash_table_remove(&t, "c", &out), 0);
  ASSERT_INT_EQ(oahash_table_remove(&t, "d", &out), 0);
  ASSERT_INT_EQ(oahash_table_remove(&t, "e", &out), 0);

  ASSERT_INT_EQ(oahash_table_insert(&t, a), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, b), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, c), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, d), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, e), 0);

  ASSERT_INT_EQ(t.size, 5);

  ASSERT_INT_EQ(oahash_table_lookup(&t, "a", &outa), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "b", &outb), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "c", &outc), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "d", &outd), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "e", &oute), 1);

  ASSERT_PTR_EQ(a, outa);
  ASSERT_PTR_EQ(b, outb);
  ASSERT_PTR_EQ(c, outc);
  ASSERT_PTR_EQ(d, outd);
  ASSERT_PTR_EQ(e, oute);

  oahash_table_destroy(&t);
}

TEST(test_insert_full) {
  OAHashTable t;
  void *out = NULL;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, "a"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "f"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "k"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "p"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "z"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "c"), 1);

  ASSERT_INT_EQ(t.size, 5);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "a", &out), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "f", &out), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "k", &out), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "p", &out), 1);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "z", &out), 1);

  oahash_table_destroy(&t);
}

TEST(test_lookup_not_exist) {
  OAHashTable t;
  void *out = NULL;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, "a"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "b"), 0);

  ASSERT_INT_EQ(oahash_table_lookup(&t, "e", &out), 0);
  ASSERT_PTR_NULL(out);

  oahash_table_destroy(&t);
}

TEST(test_lookup_exists) {
  OAHashTable t;
  char *c = "c";
  void *out = NULL;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, "a"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "b"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, c), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "d"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "e"), 0);

  ASSERT_INT_EQ(oahash_table_lookup(&t, "c", &out), 1);
  ASSERT_PTR_EQ(c, out);

  oahash_table_destroy(&t);
}

TEST(test_remove_non_existent) {
  OAHashTable t;
  void *out = NULL;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, "a"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "b"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "c"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "d"), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, "e"), 0);

  ASSERT_INT_EQ(oahash_table_remove(&t, "z", &out), 1);
  ASSERT_INT_EQ(t.size, 5);
  ASSERT_PTR_NULL(out);

  oahash_table_destroy(&t);
}

TEST(test_remove_existent) {
  OAHashTable t;
  void *a = "a";
  void *b = "b";
  void *c = "c";
  void *d = "d";
  void *e = "e";
  void *out;
  void *outa = NULL;
  void *outb = NULL;
  void *outc = NULL;
  void *outd = NULL;
  void *oute = NULL;
  ASSERT_INT_EQ(oahash_table_init(&t, 5, (unsigned long (*)(const void *))djb2,
                                  (unsigned long (*)(const void *))h2,
                                  (int (*)(const void *, const void *))strcmp,
                                  NULL),
                0);

  ASSERT_INT_EQ(oahash_table_insert(&t, a), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, b), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, c), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, d), 0);
  ASSERT_INT_EQ(oahash_table_insert(&t, e), 0);

  ASSERT_INT_EQ(oahash_table_remove(&t, "a", &outa), 0);
  ASSERT_INT_EQ(oahash_table_remove(&t, "b", &outb), 0);
  ASSERT_INT_EQ(oahash_table_remove(&t, "c", &outc), 0);
  ASSERT_INT_EQ(oahash_table_remove(&t, "d", &outd), 0);
  ASSERT_INT_EQ(oahash_table_remove(&t, "e", &oute), 0);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_PTR_EQ(a, outa);
  ASSERT_PTR_EQ(b, outb);
  ASSERT_PTR_EQ(c, outc);
  ASSERT_PTR_EQ(d, outd);
  ASSERT_PTR_EQ(e, oute);

  ASSERT_INT_EQ(oahash_table_lookup(&t, "a", &out), 0);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "b", &out), 0);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "c", &out), 0);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "d", &out), 0);
  ASSERT_INT_EQ(oahash_table_lookup(&t, "e", &out), 0);

  oahash_table_destroy(&t);
}

int main(void) {
  RUN_TEST(test_init);
  RUN_TEST(test_insert);
  RUN_TEST(test_insert_collide);
  RUN_TEST(test_insert_multi_collide);
  RUN_TEST(test_lookup_not_exist);
  RUN_TEST(test_lookup_exists);
  RUN_TEST(test_insert_full);
  RUN_TEST(test_remove_non_existent);
  RUN_TEST(test_remove_existent);
  RUN_TEST(test_reinsert);
  RUN_TEST(test_insert_duplicate);
  return 0;
}
