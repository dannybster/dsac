#include "../test_helpers.h"
#include "stack.h"
#include <assert.h>
#include <string.h>

TEST(test_init) {
  Stack stack;
  stack_init(&stack, free, 5);

  ASSERT_INT_EQ(stack.buffer_size, 5);
  ASSERT_INT_EQ(stack.size, 0);
  ASSERT_PTR_NOT_NULL(stack.elements);
  assert(stack.destroy == free);

  stack_destroy(&stack);
}

TEST(test_empty_pop) {
  Stack stack;
  void *data;
  stack_init(&stack, NULL, 5);

  ASSERT_INT_EQ(stack_pop(&stack, &data), -1);
  ASSERT_INT_EQ(stack.buffer_size, 5);
  ASSERT_INT_EQ(stack.size, 0);
  ASSERT_PTR_NOT_NULL(stack.elements);

  stack_destroy(&stack);
}

TEST(test_pop) {
  Stack stack;
  void *data;
  stack_init(&stack, NULL, 2);

  stack_push(&stack, "a");
  stack_push(&stack, "b");
  stack_push(&stack, "c");

  ASSERT_INT_EQ(stack_pop(&stack, &data), 0);
  ASSERT_STR_EQ(data, "c");
  ASSERT_INT_EQ(stack.buffer_size, 4);
  ASSERT_INT_EQ(stack.size, 2);

  ASSERT_INT_EQ(stack_peek(&stack, &data), 0);
  ASSERT_STR_EQ(data, "b");

  stack_destroy(&stack);
}

TEST(test_pop_until_empty) {
  Stack stack;
  void *data;
  stack_init(&stack, NULL, 2);

  stack_push(&stack, "a");
  stack_push(&stack, "b");
  stack_push(&stack, "c");

  ASSERT_INT_EQ(stack_pop(&stack, &data), 0);
  ASSERT_INT_EQ(stack_pop(&stack, &data), 0);
  ASSERT_INT_EQ(stack_pop(&stack, &data), 0);
  ASSERT_INT_EQ(stack_pop(&stack, &data), -1);

  ASSERT_INT_EQ(stack.buffer_size, 4);
  ASSERT_INT_EQ(stack.size, 0);

  stack_destroy(&stack);
}

TEST(test_push) {
  Stack stack;
  stack_init(&stack, NULL, 5);

  stack_push(&stack, "c");
  stack_push(&stack, "b");
  stack_push(&stack, "a");

  ASSERT_INT_EQ(stack.buffer_size, 5);
  ASSERT_INT_EQ(stack.size, 3);
  ASSERT_PTR_NOT_NULL(stack.elements);

  stack_destroy(&stack);
}

TEST(test_push_grow) {
  Stack stack;
  stack_init(&stack, NULL, 2);

  ASSERT_INT_EQ(stack_push(&stack, "l"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "k"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "j"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "i"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "h"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "g"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "f"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "e"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "d"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "c"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "b"), 0);
  ASSERT_INT_EQ(stack_push(&stack, "a"), 0);

  ASSERT_INT_EQ(stack.buffer_size, 16);
  ASSERT_INT_EQ(stack.size, 12);
  ASSERT_PTR_NOT_NULL(stack.elements);

  stack_destroy(&stack);
}

TEST(test_peek_empty) {
  Stack stack;
  void *data = NULL;

  stack_init(&stack, NULL, 2);

  ASSERT_INT_EQ(stack_peek(&stack, &data), -1);
  ASSERT_PTR_NULL(data);

  stack_destroy(&stack);
}

TEST(test_stack_peek) {
  Stack stack;
  void *data = NULL;

  stack_init(&stack, NULL, 2);
  stack_push(&stack, "a");
  stack_push(&stack, "b");
  stack_push(&stack, "c");

  ASSERT_INT_EQ(stack_peek(&stack, &data), 0);
  ASSERT_STR_EQ(data, "c");

  stack_destroy(&stack);
}

int main(void) {
  RUN_TEST(test_init);
  RUN_TEST(test_empty_pop);
  RUN_TEST(test_pop);
  RUN_TEST(test_pop_until_empty);
  RUN_TEST(test_push);
  RUN_TEST(test_push_grow);
  RUN_TEST(test_peek_empty);
  RUN_TEST(test_stack_peek);
  return 0;
}
