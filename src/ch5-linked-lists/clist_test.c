#include "../test_helpers.h"
#include "clist.h"
#include <assert.h>
#include <stdlib.h>

TEST(test_init) {
  CList list;
  clist_init(&list, free);

  ASSERT_INT_EQ(list.size, 0);
  assert(list.destroy == free);
  ASSERT_PTR_NULL(list.head);
  ASSERT_PTR_NULL(list.tail);

  clist_destroy(&list);
}

TEST(test_insert_next_empty) {
  CList list;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);

  ASSERT_INT_EQ(list.size, 1);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.tail->data, "a");

  // Ensure we are circular i.e. with one element head points
  // to head
  assert(list.head == list.tail);
  assert(list.head->next == list.head);
  assert(list.tail->next == list.head);

  clist_destroy(&list);
}

TEST(test_insert_next_head) {
  CList list;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "c"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "b"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);

  ASSERT_INT_EQ(list.size, 3);

  // Check the data.
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.head->next->next->data, "c");

  // Check the tail
  ASSERT_PTR_EQ(list.head->next->next, list.tail);

  // Check that the list is circular.
  ASSERT_PTR_EQ(list.head->next->next->next, list.head);
  ASSERT_PTR_EQ(list.tail->next, list.head);

  clist_destroy(&list);
}

TEST(test_insert_next_tail) {
  CList list;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.tail, "b"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.tail, "c"), 0);

  ASSERT_INT_EQ(list.size, 3);

  // Check the data.
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.head->next->next->data, "c");

  // Check the tail
  ASSERT_PTR_EQ(list.head->next->next, list.tail);

  // Check that the list is circular.
  ASSERT_PTR_EQ(list.head->next->next->next, list.head);
  ASSERT_PTR_EQ(list.tail->next, list.head);

  clist_destroy(&list);
}

TEST(test_insert_next_middle) {
  CList list;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.tail, "c"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head, "b"), 0);

  ASSERT_INT_EQ(list.size, 3);

  // Check the data.
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.head->next->next->data, "c");

  // Check the tail
  ASSERT_PTR_EQ(list.head->next->next, list.tail);

  // Check that the list is circular.
  ASSERT_PTR_EQ(list.head->next->next->next, list.head);
  ASSERT_PTR_EQ(list.tail->next, list.head);

  clist_destroy(&list);
}

TEST(test_remove_head_null) {
  CList list;
  char *data = NULL;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head, "b"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head->next, "c"), 0);

  clist_remove_next(&list, NULL, (void **)&data);

  // Returns correct data.
  ASSERT_STR_EQ(data, "a");

  // Assert size is decremented
  ASSERT_INT_EQ(list.size, 2);

  // List Data
  ASSERT_STR_EQ(list.head->data, "b");
  ASSERT_STR_EQ(list.tail->data, "c");

  // Assert Pointers
  assert(list.head->next == list.tail);
  assert(list.tail->next == list.head);

  clist_destroy(&list);
}

TEST(test_remove_head_tail) {
  CList list;
  char *data = NULL;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head, "b"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head->next, "c"), 0);

  clist_remove_next(&list, list.tail, (void **)&data);

  // Returns correct data.
  ASSERT_STR_EQ(data, "a");

  // Assert size is decremented
  ASSERT_INT_EQ(list.size, 2);

  // List Data
  ASSERT_STR_EQ(list.head->data, "b");
  ASSERT_STR_EQ(list.tail->data, "c");

  // Assert Pointers
  assert(list.head->next == list.tail);
  assert(list.tail->next == list.head);

  clist_destroy(&list);
}

TEST(test_remove_head_two_elements) {
  CList list;
  char *data = NULL;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head, "b"), 0);

  clist_remove_next(&list, NULL, (void **)&data);

  // Returns correct data.
  ASSERT_STR_EQ(data, "a");

  // Assert size is decremented
  ASSERT_INT_EQ(list.size, 1);

  // Assert list structure is still fine
  assert(list.head == list.tail);
  assert(list.head->next == list.head);

  // Assert list values are still correct
  ASSERT_STR_EQ(list.head->data, "b");

  clist_destroy(&list);
}

TEST(test_remove_tail) {
  CList list;
  char *data = NULL;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head, "b"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head->next, "c"), 0);

  clist_remove_next(&list, list.head->next, (void **)&data);

  // Returns correct data.
  ASSERT_STR_EQ(data, "c");

  // Assert size is decremented
  ASSERT_INT_EQ(list.size, 2);

  // Assert list data.
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.tail->data, "b");
  ASSERT_STR_EQ(list.tail->next->data, "a");

  // Assert list structure
  ASSERT_PTR_EQ(list.head->next, list.tail);
  ASSERT_PTR_EQ(list.tail->next, list.head);

  clist_destroy(&list);
}

TEST(test_remove_middle) {
  CList list;
  char *data = NULL;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head, "b"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head->next, "c"), 0);

  clist_remove_next(&list, list.head, (void **)&data);

  // Assert return value.
  ASSERT_STR_EQ(data, "b");

  // Assert length has been decremented.
  ASSERT_INT_EQ(list.size, 2);

  // Assert contents are as expectd.
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "c");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_STR_EQ(list.tail->next->data, "a");

  // Assert list structure.
  ASSERT_PTR_EQ(list.head->next, list.tail);
  ASSERT_PTR_EQ(list.tail->next, list.head);

  clist_destroy(&list);
}

TEST(test_remove_all) {
  CList list;
  char *data = NULL;
  clist_init(&list, NULL);

  ASSERT_INT_EQ(clist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head, "b"), 0);
  ASSERT_INT_EQ(clist_insert_next(&list, list.head->next, "c"), 0);

  clist_remove_next(&list, list.head, (void *)&data);
  clist_remove_next(&list, list.head, (void *)&data);
  clist_remove_next(&list, list.head, (void *)&data);

  // Assert list is empty
  ASSERT_INT_EQ(list.size, 0);
  ASSERT_PTR_NULL(list.head);
  ASSERT_PTR_NULL(list.tail);
}

int main(void) {
  RUN_TEST(test_init);
  RUN_TEST(test_insert_next_empty);
  RUN_TEST(test_insert_next_head);
  RUN_TEST(test_insert_next_tail);
  RUN_TEST(test_insert_next_middle);
  RUN_TEST(test_remove_head_null);
  RUN_TEST(test_remove_head_tail);
  RUN_TEST(test_remove_head_two_elements);
  RUN_TEST(test_remove_tail);
  RUN_TEST(test_remove_middle);
  RUN_TEST(test_remove_all);
  return 0;
}
