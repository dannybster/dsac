#include "../test_helpers.h"
#include "queue.h"

TEST(test_queue_init) {
  Queue queue;
  queue_init(&queue, NULL);

  ASSERT_INT_EQ(queue_size(&queue), 0);

  queue_destroy(&queue);
}

TEST(test_peek_empty) {
  Queue queue;
  void *data = NULL;
  queue_init(&queue, NULL);

  ASSERT_INT_EQ(queue_peek(&queue, &data), -1);
  ASSERT_PTR_NULL(data);

  queue_destroy(&queue);
}

TEST(test_peek) {
  Queue queue;
  void *data = NULL;
  queue_init(&queue, NULL);

  ASSERT_INT_EQ(queue_enqueue(&queue, "a"), 0);
  ASSERT_INT_EQ(queue_enqueue(&queue, "b"), 0);
  ASSERT_INT_EQ(queue_enqueue(&queue, "c"), 0);

  ASSERT_INT_EQ(queue_peek(&queue, &data), 0);
  ASSERT_STR_EQ(data, "a");

  queue_destroy(&queue);
}

TEST(test_enqueue) {
  Queue queue;
  queue_init(&queue, NULL);

  ASSERT_INT_EQ(queue_enqueue(&queue, "a"), 0);
  ASSERT_INT_EQ(queue_enqueue(&queue, "b"), 0);
  ASSERT_INT_EQ(queue_enqueue(&queue, "c"), 0);

  ASSERT_INT_EQ(queue_size(&queue), 3);

  queue_destroy(&queue);
}

TEST(test_dequeue_empty) {
  Queue queue;
  void *data = NULL;
  queue_init(&queue, NULL);

  ASSERT_INT_EQ(queue_dequeue(&queue, &data), -1);
  ASSERT_PTR_NULL(data);

  queue_destroy(&queue);
}

TEST(test_dequeue) {
  Queue queue;
  void *data = NULL;
  queue_init(&queue, NULL);

  ASSERT_INT_EQ(queue_enqueue(&queue, "a"), 0);
  ASSERT_INT_EQ(queue_enqueue(&queue, "b"), 0);
  ASSERT_INT_EQ(queue_enqueue(&queue, "c"), 0);

  ASSERT_INT_EQ(queue_dequeue(&queue, &data), 0);
  ASSERT_INT_EQ(queue_size(&queue), 2);
  ASSERT_STR_EQ(data, "a");

  queue_destroy(&queue);
}

TEST(test_dequeue_all) {
  Queue queue;
  void *data = NULL;
  queue_init(&queue, NULL);

  ASSERT_INT_EQ(queue_enqueue(&queue, "a"), 0);
  ASSERT_INT_EQ(queue_enqueue(&queue, "b"), 0);
  ASSERT_INT_EQ(queue_enqueue(&queue, "c"), 0);

  ASSERT_INT_EQ(queue_dequeue(&queue, &data), 0);
  ASSERT_INT_EQ(queue_dequeue(&queue, &data), 0);
  ASSERT_INT_EQ(queue_dequeue(&queue, &data), 0);
  ASSERT_INT_EQ(queue_dequeue(&queue, &data), -1);

  ASSERT_INT_EQ(queue_size(&queue), 0);
  ASSERT_STR_EQ(data, "c");

  queue_destroy(&queue);
}

int main(void) {
  RUN_TEST(test_queue_init);
  RUN_TEST(test_peek_empty);
  RUN_TEST(test_peek);
  RUN_TEST(test_enqueue);
  RUN_TEST(test_dequeue_empty);
  RUN_TEST(test_dequeue);
  RUN_TEST(test_dequeue_all);
  return 0;
}
