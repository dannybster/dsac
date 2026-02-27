#include "../test_helpers.h"
#include "chhash_table.h"
#include "djb2.h"

TEST(test_init) {
  CHHashTable t;
  chhash_table_init(&t, 5, free, (int (*)(const void *, const void *))strcmp,
                    djb2);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_INT_EQ(t.buckets, 5);
  ASSERT_PTR_EQ((void *)t.h, (void *)djb2);
  ASSERT_PTR_EQ((void *)t.match, (void *)strcmp);
  ASSERT_PTR_NOT_NULL(t.table);

  for (int i = 0; i < 5; i++) {
    ASSERT_PTR_EQ((void *)t.table[i].destroy, (void *)free);
  }

  chhash_table_destroy(&t);
}

TEST(test_insert_unique) {
  CHHashTable t;
  chhash_table_init(&t, 5, NULL, (int (*)(const void *, const void *))strcmp,
                    djb2);

  ASSERT_INT_EQ(chhash_table_insert(&t, "0"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "1"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "2"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "3"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "4"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "5"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "6"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "7"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "8"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "9"), 0);

  ASSERT_INT_EQ(t.size, 10);

  chhash_table_destroy(&t);
}

TEST(test_insert_duplicate) {
  CHHashTable t;
  chhash_table_init(&t, 5, NULL, (int (*)(const void *, const void *))strcmp,
                    djb2);

  ASSERT_INT_EQ(chhash_table_insert(&t, "0"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "1"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "2"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "3"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "4"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "5"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "6"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "7"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "8"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "9"), 0);

  ASSERT_INT_EQ(chhash_table_insert(&t, "2"), 1);
  ASSERT_INT_EQ(t.size, 10);

  chhash_table_destroy(&t);
}

TEST(test_lookup_non_existent) {
  CHHashTable t;
  void *out = NULL;
  chhash_table_init(&t, 5, NULL, (int (*)(const void *, const void *))strcmp,
                    djb2);

  ASSERT_INT_EQ(chhash_table_insert(&t, "0"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "1"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "2"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "3"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "4"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "5"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "6"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "7"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "8"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "9"), 0);

  ASSERT_INT_EQ(chhash_table_lookup(&t, "18", &out), 0);
  ASSERT_PTR_NULL(out);

  chhash_table_destroy(&t);
}

TEST(test_lookup_exists) {
  CHHashTable t;
  void *out = NULL;
  void *data = "7";
  chhash_table_init(&t, 5, NULL, (int (*)(const void *, const void *))strcmp,
                    djb2);

  ASSERT_INT_EQ(chhash_table_insert(&t, "0"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "1"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "2"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "3"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "4"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "5"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "6"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, data), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "8"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "9"), 0);

  ASSERT_INT_EQ(chhash_table_lookup(&t, "7", &out), 1);
  ASSERT_PTR_EQ(data, out);

  chhash_table_destroy(&t);
}

TEST(test_remove_non_existent) {
  CHHashTable t;
  void *out = NULL;
  chhash_table_init(&t, 5, NULL, (int (*)(const void *, const void *))strcmp,
                    djb2);

  ASSERT_INT_EQ(chhash_table_insert(&t, "0"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "1"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "2"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "3"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "4"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "5"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "6"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "8"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "9"), 0);

  ASSERT_INT_EQ(chhash_table_remove(&t, "7", &out), 1);
  ASSERT_INT_EQ(t.size, 9);
  ASSERT_PTR_NULL(out);

  chhash_table_destroy(&t);
}

TEST(test_remove_existent) {
  CHHashTable t;
  void *data = "7";
  void *out = NULL;
  chhash_table_init(&t, 5, NULL, (int (*)(const void *, const void *))strcmp,
                    djb2);

  ASSERT_INT_EQ(chhash_table_insert(&t, "0"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "1"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "2"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "3"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "4"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "5"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "6"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "7"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "8"), 0);
  ASSERT_INT_EQ(chhash_table_insert(&t, "9"), 0);

  ASSERT_INT_EQ(chhash_table_remove(&t, "7", &out), 0);
  ASSERT_INT_EQ(t.size, 9);
  ASSERT_PTR_EQ(data, out);

  chhash_table_destroy(&t);
}

int main(void) {
  RUN_TEST(test_init);
  RUN_TEST(test_insert_unique);
  RUN_TEST(test_insert_duplicate);
  RUN_TEST(test_lookup_non_existent);
  RUN_TEST(test_lookup_exists);
  RUN_TEST(test_remove_non_existent);
  RUN_TEST(test_remove_existent);
  return 0;
}
