#include "../test_helpers.h"
#include "list.h"
#include <assert.h>
#include <string.h>

TEST(test_list_init) {
  List list;
  list_init(&list, free);

  assert(list.size == 0);
  assert(list.match == NULL);
  assert(list.destroy == free);
  assert(list.head == NULL);
  assert(list.tail == NULL);

  list_destroy(&list);
}

TEST(test_list_ins_first_head) {
  List list;
  list_init(&list, NULL);

  assert(list_insert_next(&list, list.head, "a") == 0);

  assert(list.size == 1);
  assert(list.head == list.tail);
  assert(strcmp(list.head->data, "a") == 0);

  list_destroy(&list);
}

TEST(test_list_ins_head) {
  List list;
  list_init(&list, NULL);

  assert(list_insert_next(&list, list.head, "b") == 0);
  assert(list_insert_next(&list, NULL, "a") == 0);

  ASSERT_INT_EQ(list.size, 2);
  ASSERT_PTR_EQ(list.head->next, list.tail);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");

  list_destroy(&list);
}

TEST(test_list_ins_middle) {
  List list;
  list_init(&list, NULL);

  assert(list_insert_next(&list, NULL, "d") == 0);
  assert(list_insert_next(&list, NULL, "b") == 0);
  assert(list_insert_next(&list, NULL, "a") == 0);

  assert(list_insert_next(&list, list.head->next, "c") == 0);

  ASSERT_INT_EQ(list.size, 4);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.head->next->next->data, "c");
  ASSERT_STR_EQ(list.head->next->next->next->data, "d");

  list_destroy(&list);
}

TEST(test_list_ins_tail) {
  List list;
  list_init(&list, NULL);

  assert(list_insert_next(&list, NULL, "b") == 0);
  assert(list_insert_next(&list, NULL, "a") == 0);
  assert(list_insert_next(&list, list.tail, "c") == 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.head->next->next->data, "c");
  ASSERT_PTR_EQ(list.head->next->next, list.tail);

  list_destroy(&list);
}

TEST(test_list_remove_empty) {
  List list;
  list_init(&list, NULL);
  int *data = NULL;

  assert(list_remove_next(&list, NULL, (void **)&data) == -1);
  ASSERT_PTR_NULL(data);

  list_destroy(&list);
}

TEST(test_list_remove_head) {
  List list;
  list_init(&list, NULL);
  char *data = NULL;

  assert(list_insert_next(&list, NULL, "b") == 0);
  assert(list_insert_next(&list, NULL, "a") == 0);
  assert(list_insert_next(&list, NULL, "z") == 0);

  assert(list_remove_next(&list, NULL, (void **)&data) == 0);

  ASSERT_INT_EQ(list.size, 2);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(data, "z");

  list_destroy(&list);
}

TEST(test_list_remove_to_empty) {
  List list;
  list_init(&list, NULL);
  char *data = NULL;

  list_insert_next(&list, NULL, "a");
  list_remove_next(&list, NULL, (void **)&data);

  ASSERT_INT_EQ(list.size, 0);
  ASSERT_PTR_NULL(list.head);
  ASSERT_PTR_NULL(list.tail);
  ASSERT_STR_EQ(data, "a");

  list_destroy(&list);
}

TEST(test_list_remove_middle) {
  List list;
  list_init(&list, NULL);
  char *data = NULL;

  assert(list_insert_next(&list, NULL, "c") == 0);
  assert(list_insert_next(&list, NULL, "z") == 0);
  assert(list_insert_next(&list, NULL, "b") == 0);
  assert(list_insert_next(&list, NULL, "a") == 0);

  assert(list_remove_next(&list, list.head->next, (void **)&data) == 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.head->next->next->data, "c");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_STR_EQ(data, "z");

  list_destroy(&list);
}

TEST(test_list_remove_tail) {
  List list;
  list_init(&list, NULL);
  char *data = NULL;

  assert(list_insert_next(&list, NULL, "z") == 0);
  assert(list_insert_next(&list, NULL, "c") == 0);
  assert(list_insert_next(&list, NULL, "b") == 0);
  assert(list_insert_next(&list, NULL, "a") == 0);

  assert(list_remove_next(&list, list.head->next->next, (void **)&data) == 0);

  ASSERT_INT_EQ(list.size, 3);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_STR_EQ(list.head->next->next->data, "c");
  ASSERT_STR_EQ(list.tail->data, "c");
  ASSERT_PTR_NULL(list.tail->next);
  ASSERT_STR_EQ(data, "z");

  list_destroy(&list);
}

TEST(test_list_remove_after_tail) {
  List list;

  list_init(&list, NULL);
  char *data = NULL;

  assert(list_insert_next(&list, NULL, "b") == 0);
  assert(list_insert_next(&list, NULL, "a") == 0);

  assert(list_remove_next(&list, list.tail, (void **)&data) == -1);

  ASSERT_INT_EQ(list.size, 2);
  ASSERT_STR_EQ(list.head->data, "a");
  ASSERT_STR_EQ(list.head->next->data, "b");
  ASSERT_PTR_NULL(data);

  list_destroy(&list);
}

TEST(test_list_destroy) {
  List list;

  list_init(&list, NULL);

  assert(list_insert_next(&list, NULL, "b") == 0);
  assert(list_insert_next(&list, NULL, "a") == 0);

  list_destroy(&list);

  ASSERT_INT_EQ(list.size, 0);
  ASSERT_PTR_NULL(list.head);
  ASSERT_PTR_NULL(list.tail);
  ASSERT_PTR_NULL(list.destroy);
}

int main(void) {
  RUN_TEST(test_list_init);
  RUN_TEST(test_list_ins_first_head);
  RUN_TEST(test_list_ins_head);
  RUN_TEST(test_list_ins_middle);
  RUN_TEST(test_list_ins_tail);
  RUN_TEST(test_list_remove_empty);
  RUN_TEST(test_list_remove_to_empty);
  RUN_TEST(test_list_remove_head);
  RUN_TEST(test_list_remove_middle);
  RUN_TEST(test_list_remove_tail);
  RUN_TEST(test_list_remove_after_tail);
  RUN_TEST(test_list_destroy);
}
