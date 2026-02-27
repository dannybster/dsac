#include "../test_helpers.h"
#include "bi_tree.h"

TEST(test_init) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, free), 0);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_PTR_NULL(t.root);
  ASSERT_PTR_EQ(t.match, strcmp);
  ASSERT_PTR_EQ(t.destroy, free);

  bitree_destroy(&t);
}

TEST(test_insert_left_root) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, a), 0);

  ASSERT_INT_EQ(t.size, 1);
  ASSERT_PTR_NOT_NULL(t.root);
  ASSERT_PTR_NULL(t.root->l);
  ASSERT_PTR_NULL(t.root->r);
  ASSERT_STR_EQ(t.root->data, a);

  bitree_destroy(&t);
}

TEST(test_insert_left_populated_root) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, a), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, "b"), 1);

  ASSERT_INT_EQ(t.size, 1);
  ASSERT_PTR_NOT_NULL(t.root);
  ASSERT_PTR_NULL(t.root->l);
  ASSERT_PTR_NULL(t.root->r);
  ASSERT_STR_EQ(t.root->data, a);

  bitree_destroy(&t);
}

TEST(test_insert_left_left) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, a), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "b"), 0);

  ASSERT_INT_EQ(t.size, 2);
  ASSERT_STR_EQ(t.root->data, a);
  ASSERT_STR_EQ(t.root->l->data, "b");

  ASSERT_PTR_NULL(t.root->r);
  ASSERT_PTR_NULL(t.root->l->l);
  ASSERT_PTR_NULL(t.root->l->r);

  bitree_destroy(&t);
}

TEST(insert_left_not_leaf) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, a), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "c"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "d"), 1);

  ASSERT_INT_EQ(t.size, 3);

  ASSERT_STR_EQ(t.root->data, a);
  ASSERT_STR_EQ(t.root->l->data, "b");
  ASSERT_STR_EQ(t.root->l->l->data, "c");

  ASSERT_PTR_NULL(t.root->r);
  ASSERT_PTR_NULL(t.root->l->r);
  ASSERT_PTR_NULL(t.root->l->l->l);
  ASSERT_PTR_NULL(t.root->l->l->r);

  bitree_destroy(&t);
}

TEST(test_insert_right_root) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, a), 0);

  ASSERT_INT_EQ(t.size, 1);
  ASSERT_PTR_NOT_NULL(t.root);
  ASSERT_PTR_NULL(t.root->l);
  ASSERT_PTR_NULL(t.root->r);
  ASSERT_STR_EQ(t.root->data, a);

  bitree_destroy(&t);
}

TEST(test_insert_right_populated_root) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, a), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, "b"), 1);

  ASSERT_INT_EQ(t.size, 1);
  ASSERT_PTR_NOT_NULL(t.root);
  ASSERT_PTR_NULL(t.root->l);
  ASSERT_PTR_NULL(t.root->r);
  ASSERT_STR_EQ(t.root->data, a);

  bitree_destroy(&t);
}

TEST(test_insert_right_right) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, a), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "b"), 0);

  ASSERT_INT_EQ(t.size, 2);
  ASSERT_STR_EQ(t.root->data, a);
  ASSERT_STR_EQ(t.root->r->data, "b");

  ASSERT_PTR_NULL(t.root->l);
  ASSERT_PTR_NULL(t.root->r->l);
  ASSERT_PTR_NULL(t.root->r->r);

  bitree_destroy(&t);
}

TEST(insert_right_not_leaf) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, a), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "c"), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "d"), 1);

  ASSERT_INT_EQ(t.size, 3);

  ASSERT_STR_EQ(t.root->data, a);
  ASSERT_STR_EQ(t.root->r->data, "b");
  ASSERT_STR_EQ(t.root->r->r->data, "c");

  ASSERT_PTR_NULL(t.root->l);
  ASSERT_PTR_NULL(t.root->r->l);
  ASSERT_PTR_NULL(t.root->r->r->l);
  ASSERT_PTR_NULL(t.root->r->r->r);

  bitree_destroy(&t);
}

int main(void) {
  RUN_TEST(test_init);
  RUN_TEST(test_insert_left_root);
  RUN_TEST(test_insert_left_populated_root);
  RUN_TEST(test_insert_left_left);
  RUN_TEST(insert_left_not_leaf);
  RUN_TEST(test_insert_right_root);
  RUN_TEST(test_insert_right_populated_root);
  RUN_TEST(test_insert_right_right);
  RUN_TEST(insert_right_not_leaf);
  return 0;
}
