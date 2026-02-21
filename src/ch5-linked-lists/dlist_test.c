#include "../test_helpers.h"
#include "dlist.h"
#include <assert.h>
#include <string.h>

TEST(test_init) {
  DList list;
  dlist_init(&list, free);

  ASSERT_INT_EQ(list.size, 0);
  ASSERT_PTR_NULL(list.head);
  ASSERT_PTR_NULL(list.tail);
  assert(list.destroy == free);
  dlist_destroy(&list);
}

TEST(destroy) {
  DList list;

  dlist_init(&list, NULL);
  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "c"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "b"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "a"), 0);

  dlist_destroy(&list);

  ASSERT_INT_EQ(list.size, 0);
  ASSERT_PTR_NULL(list.head);
  ASSERT_PTR_NULL(list.tail);
}

TEST(insert_next_when_empty) {
  DList list;

  dlist_init(&list, NULL);
  dlist_insert_next(&list, NULL, "a");

  ASSERT_INT_EQ(list.size, 1);
  ASSERT_PTR_NOT_NULL(list.head);
  ASSERT_PTR_NOT_NULL(list.tail);
  ASSERT_PTR_EQ(list.head, list.tail);

  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_PTR_NULL(list.head->next);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);

  dlist_destroy(&list);
}

TEST(insert_next_head) {
  DList list;

  dlist_init(&list, NULL);
  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "c"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "b"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "a"), 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.tail->previous->data, "b");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_PTR_EQ(list.head->next->previous, list.head);
  ASSERT_PTR_EQ(list.head->next->next, list.tail);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(insert_next_tail) {
  DList list;

  dlist_init(&list, NULL);
  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, list.head, "b"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, list.head->next, "c"), 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.tail->previous->data, "b");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_PTR_EQ(list.head->next->previous, list.head);
  ASSERT_PTR_EQ(list.head->next->next, list.tail);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(insert_next_middle) {
  DList list;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, list.head, "c"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, list.head, "b"), 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.tail->previous->data, "b");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_PTR_EQ(list.head->next->previous, list.head);
  ASSERT_PTR_EQ(list.head->next->next, list.tail);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(insert_previous_when_empty) {
  DList list;

  dlist_init(&list, NULL);
  dlist_insert_previous(&list, NULL, "a");

  ASSERT_INT_EQ(list.size, 1);
  ASSERT_PTR_NOT_NULL(list.head);
  ASSERT_PTR_NOT_NULL(list.tail);
  ASSERT_PTR_EQ(list.head, list.tail);

  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_PTR_NULL(list.head->next);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(insert_previous_tail) {
  DList list;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_insert_previous(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(dlist_insert_previous(&list, NULL, "b"), 0);
  ASSERT_INT_EQ(dlist_insert_previous(&list, NULL, "c"), 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.tail->previous->data, "b");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_PTR_EQ(list.head->next->previous, list.head);
  ASSERT_PTR_EQ(list.head->next->next, list.tail);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(insert_previous_head) {
  DList list;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_insert_previous(&list, list.head, "c"), 0);
  ASSERT_INT_EQ(dlist_insert_previous(&list, list.head, "b"), 0);
  ASSERT_INT_EQ(dlist_insert_previous(&list, list.head, "a"), 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.tail->previous->data, "b");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_PTR_EQ(list.head->next->previous, list.head);
  ASSERT_PTR_EQ(list.head->next->next, list.tail);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(insert_previous_middle) {
  DList list;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_insert_previous(&list, NULL, "c"), 0);
  ASSERT_INT_EQ(dlist_insert_previous(&list, list.tail, "a"), 0);
  ASSERT_INT_EQ(dlist_insert_previous(&list, list.tail, "b"), 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.tail->previous->data, "b");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_PTR_EQ(list.head->next->previous, list.head);
  ASSERT_PTR_EQ(list.head->next->next, list.tail);
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(remove_when_empty) {
  DList list;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_remove(&list, NULL, NULL), -1);
  ASSERT_INT_EQ(list.size, 0);
  ASSERT_PTR_NULL(list.head);
  ASSERT_PTR_NULL(list.tail);
  dlist_destroy(&list);
}

TEST(remove_only_item) {
  DList list;
  char *data = NULL;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(dlist_remove(&list, list.head, (void **)&data), 0);

  ASSERT_STR_EQ(data, "a");
  ASSERT_INT_EQ(list.size, 0);
  ASSERT_PTR_NULL(list.head);
  ASSERT_PTR_NULL(list.tail);
  dlist_destroy(&list);
}

TEST(remove_head) {
  DList list;
  char *data = NULL;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "z"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, list.head, "a"), 0);

  ASSERT_INT_EQ(dlist_remove(&list, list.head, (void **)&data), 0);

  ASSERT_STR_EQ(data, "z");
  ASSERT_INT_EQ(list.size, 1);
  ASSERT_PTR_EQ(list.head, list.tail);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(remove_tail) {
  DList list;
  char *data = NULL;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, list.head, "b"), 0);

  ASSERT_INT_EQ(dlist_remove(&list, list.tail, (void **)&data), 0);

  ASSERT_STR_EQ(data, "b");
  ASSERT_INT_EQ(list.size, 1);
  ASSERT_PTR_EQ(list.head, list.tail);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_NULL(list.tail->next);
  dlist_destroy(&list);
}

TEST(remove_middle) {
  DList list;
  char *data = NULL;
  dlist_init(&list, NULL);

  ASSERT_INT_EQ(dlist_insert_next(&list, NULL, "a"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, list.head, "z"), 0);
  ASSERT_INT_EQ(dlist_insert_next(&list, list.head->next, "b"), 0);
  ASSERT_INT_EQ(dlist_remove(&list, list.head->next, (void **)&data), 0);

  ASSERT_STR_EQ(data, "z");
  ASSERT_INT_EQ(list.size, 2);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_PTR_NULL(list.head->previous);
  ASSERT_PTR_EQ(list.head->next, list.tail);
  ASSERT_STR_EQ(list.tail->data, "b");
  ASSERT_PTR_NULL(list.tail->next);
  ASSERT_PTR_EQ(list.tail->previous, list.head);
  dlist_destroy(&list);
}

int main(void) {
  RUN_TEST(test_init);
  RUN_TEST(insert_next_when_empty);
  RUN_TEST(insert_next_head);
  RUN_TEST(insert_next_tail);
  RUN_TEST(insert_next_middle);
  RUN_TEST(insert_previous_when_empty);
  RUN_TEST(insert_previous_head);
  RUN_TEST(insert_previous_tail);
  RUN_TEST(insert_previous_middle);
  RUN_TEST(remove_when_empty);
  RUN_TEST(remove_only_item);
  RUN_TEST(remove_head);
  RUN_TEST(remove_tail);
  RUN_TEST(remove_middle);
  RUN_TEST(destroy);
}
