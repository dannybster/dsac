#include "../test_helpers.h"
#include "heap.h"

int cmp(const int *l, const int *r) {
  if (*l > *r)
    return 1;
  else if (*l < *r)
    return -1;
  else
    return 0;
}

TEST(test_heap_init) {
  Heap h;
  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, free),
                0);

  ASSERT_INT_EQ(heap_size(&h), 0);
  ASSERT_PTR_NULL(h.data);
  ASSERT_PTR_EQ(cmp, h.cmp);
  ASSERT_PTR_EQ(free, h.destroy);

  heap_destroy(&h);
}

TEST(test_insert_empty) {
  Heap h;
  int data = 100;
  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, NULL),
                0);

  ASSERT_INT_EQ(heap_insert(&h, &data), 0);

  ASSERT_INT_EQ(heap_size(&h), 1);
  ASSERT_INT_EQ(*(int *)*h.data, data);

  heap_destroy(&h);
}

TEST(test_insert_ordered_value) {
  Heap h;
  int p = 20;
  int l = 12;

  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, NULL),
                0);

  ASSERT_INT_EQ(heap_insert(&h, &p), 0);
  ASSERT_INT_EQ(heap_insert(&h, &l), 0);

  ASSERT_INT_EQ(heap_size(&h), 2);
  ASSERT_INT_EQ(*(int *)h.data[0], p);
  ASSERT_INT_EQ(*(int *)h.data[1], l);

  heap_destroy(&h);
}

TEST(test_insert_unordered_value) {
  Heap h;
  int p = 20;
  int l = 12;

  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, NULL),
                0);

  ASSERT_INT_EQ(heap_insert(&h, &l), 0);
  ASSERT_INT_EQ(heap_insert(&h, &p), 0);

  ASSERT_INT_EQ(heap_size(&h), 2);
  ASSERT_INT_EQ(*(int *)h.data[0], p);
  ASSERT_INT_EQ(*(int *)h.data[1], l);

  heap_destroy(&h);
}

TEST(test_insert_unorderd_value_real_world) {
  Heap h;
  int a = 12;
  int b = 22;
  int c = 19;
  int d = 40;
  int e = 32;
  int f = 90;
  int g = 100;

  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, NULL),
                0);

  ASSERT_INT_EQ(heap_insert(&h, &a), 0);
  ASSERT_INT_EQ(heap_insert(&h, &b), 0);
  ASSERT_INT_EQ(heap_insert(&h, &c), 0);
  ASSERT_INT_EQ(heap_insert(&h, &d), 0);
  ASSERT_INT_EQ(heap_insert(&h, &e), 0);
  ASSERT_INT_EQ(heap_insert(&h, &f), 0);

  // Insert value that bubbles all the way to root.
  ASSERT_INT_EQ(heap_insert(&h, &g), 0);

  ASSERT_INT_EQ(heap_size(&h), 7);

  // Expected max-heap: [100, 32, 90, 12, 22, 19, 40]
  ASSERT_INT_EQ(*(int *)h.data[0], 100);
  ASSERT_INT_EQ(*(int *)h.data[1], 32);
  ASSERT_INT_EQ(*(int *)h.data[2], 90);
  ASSERT_INT_EQ(*(int *)h.data[3], 12);
  ASSERT_INT_EQ(*(int *)h.data[4], 22);
  ASSERT_INT_EQ(*(int *)h.data[5], 19);
  ASSERT_INT_EQ(*(int *)h.data[6], 40);

  heap_destroy(&h);
}

TEST(test_extract_empty) {
  Heap h;
  void *out = NULL;
  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, NULL),
                0);

  ASSERT_INT_EQ(heap_extract(&h, &out), -1);
  ASSERT_PTR_NULL(out);

  heap_destroy(&h);
}

TEST(test_extract_only) {
  Heap h;
  int p = 20;
  void *out = NULL;
  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, NULL),
                0);

  ASSERT_INT_EQ(heap_insert(&h, &p), 0);
  ASSERT_INT_EQ(heap_extract(&h, &out), 0);

  ASSERT_PTR_EQ(out, &p);
  ASSERT_INT_EQ(heap_size(&h), 0);
  ASSERT_PTR_NULL(h.data);

  heap_destroy(&h);
}

TEST(test_extract_single_ordered) {
  Heap h;
  int p = 50;
  int l = 30;
  int r = 45;
  void *out = NULL;

  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, NULL),
                0);

  ASSERT_INT_EQ(heap_insert(&h, &p), 0);
  ASSERT_INT_EQ(heap_insert(&h, &l), 0);
  ASSERT_INT_EQ(heap_insert(&h, &r), 0);

  ASSERT_INT_EQ(heap_extract(&h, &out), 0);
  ASSERT_PTR_EQ(out, &p);
  ASSERT_INT_EQ(heap_size(&h), 2);

  ASSERT_INT_EQ(*(int *)h.data[0], r);
  ASSERT_INT_EQ(*(int *)h.data[1], l);

  heap_destroy(&h);
}

TEST(test_extract_single_unordered) {
  Heap h;
  int p = 50;
  int l = 45;
  int r = 30;
  void *out = NULL;

  ASSERT_INT_EQ(heap_init(&h, (int (*)(const void *, const void *))cmp, NULL),
                0);

  ASSERT_INT_EQ(heap_insert(&h, &p), 0);
  ASSERT_INT_EQ(heap_insert(&h, &l), 0);
  ASSERT_INT_EQ(heap_insert(&h, &r), 0);

  ASSERT_INT_EQ(heap_extract(&h, &out), 0);
  ASSERT_PTR_EQ(out, &p);
  ASSERT_INT_EQ(heap_size(&h), 2);

  ASSERT_INT_EQ(*(int *)h.data[0], l);
  ASSERT_INT_EQ(*(int *)h.data[1], r);

  heap_destroy(&h);
}

int main(void) {
  RUN_TEST(test_heap_init);
  RUN_TEST(test_insert_empty);
  RUN_TEST(test_insert_ordered_value);
  RUN_TEST(test_insert_unordered_value);
  RUN_TEST(test_insert_unorderd_value_real_world);
  RUN_TEST(test_extract_empty);
  RUN_TEST(test_extract_only);
  RUN_TEST(test_extract_single_ordered);
  RUN_TEST(test_extract_single_unordered);
  return 0;
}
