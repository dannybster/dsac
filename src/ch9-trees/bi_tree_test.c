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

TEST(test_insert_right_not_leaf) {
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

TEST(insert_right_left_tree) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  /*
   *          a
   *         /
   *        b
   *       / \
   *      c   d
   */
  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, a), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "b"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "c"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->l, "d"), 0);

  ASSERT_INT_EQ(t.size, 4);
  ASSERT_STR_EQ(t.root->data, "a");
  ASSERT_STR_EQ(t.root->l->data, "b");
  ASSERT_STR_EQ(t.root->l->l->data, "c");
  ASSERT_STR_EQ(t.root->l->r->data, "d");

  bitree_destroy(&t);
}

TEST(test_remove_left_empty) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  bitree_remove_left(&t, NULL);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_PTR_NULL(t.root);

  bitree_destroy(&t);
}

TEST(test_remove_left_root_only) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, a), 0);
  bitree_remove_left(&t, NULL);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_PTR_NULL(t.root);

  bitree_destroy(&t);
}

TEST(test_remove_left_leaf) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, "a"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "c"), 0);

  bitree_remove_left(&t, t.root->l);

  ASSERT_INT_EQ(t.size, 2);

  ASSERT_STR_EQ(t.root->data, "a");
  ASSERT_STR_EQ(t.root->l->data, "b");

  ASSERT_PTR_NULL(t.root->l->l);
  ASSERT_PTR_NULL(t.root->l->r);

  bitree_destroy(&t);
}

TEST(test_remove_left_leaf_null) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, "a"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "c"), 0);

  bitree_remove_left(&t, t.root->l->l);

  ASSERT_INT_EQ(t.size, 3);

  ASSERT_STR_EQ(t.root->data, "a");
  ASSERT_STR_EQ(t.root->l->data, "b");
  ASSERT_STR_EQ(t.root->l->l->data, "c");

  bitree_destroy(&t);
}

// This test requires running with leaks to confirm we didn't just
// cut the tree without tidying up the children.
TEST(test_remove_left_branch) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, "a"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "c"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l->l, "d"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l->l->l, "e"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l->l->l->l, "f"), 0);

  bitree_remove_left(&t, t.root->l->l);

  ASSERT_INT_EQ(t.size, 3);

  ASSERT_STR_EQ(t.root->data, "a");
  ASSERT_STR_EQ(t.root->l->data, "b");
  ASSERT_STR_EQ(t.root->l->l->data, "c");

  ASSERT_PTR_NULL(t.root->l->l->r);
  ASSERT_PTR_NULL(t.root->l->l->l);

  bitree_destroy(&t);
}

TEST(test_remove_right_empty) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  bitree_remove_right(&t, NULL);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_PTR_NULL(t.root);

  bitree_destroy(&t);
}

TEST(test_remove_right_root_only) {
  BiTree t;
  char *a = "a";
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, a), 0);
  bitree_remove_right(&t, NULL);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_PTR_NULL(t.root);

  bitree_destroy(&t);
}

TEST(test_remove_right_leaf) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, "a"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "c"), 0);

  bitree_remove_right(&t, t.root->r);

  ASSERT_INT_EQ(t.size, 2);

  ASSERT_STR_EQ(t.root->data, "a");
  ASSERT_STR_EQ(t.root->r->data, "b");

  ASSERT_PTR_NULL(t.root->r->l);
  ASSERT_PTR_NULL(t.root->r->r);

  bitree_destroy(&t);
}

TEST(test_remove_right_leaf_null) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, "a"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "c"), 0);

  bitree_remove_right(&t, t.root->r->r);

  ASSERT_INT_EQ(t.size, 3);

  ASSERT_STR_EQ(t.root->data, "a");
  ASSERT_STR_EQ(t.root->r->data, "b");
  ASSERT_STR_EQ(t.root->r->r->data, "c");

  bitree_destroy(&t);
}
//
// This test requires running with leaks to confirm we didn't just
// cut the tree without tidying up the children.
TEST(test_remove_right_branch) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, "a"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "c"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r->r, "d"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r->r->r, "e"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r->r->r->r, "f"), 0);

  bitree_remove_right(&t, t.root->r->r);

  ASSERT_INT_EQ(t.size, 3);

  ASSERT_STR_EQ(t.root->data, "a");
  ASSERT_STR_EQ(t.root->r->data, "b");
  ASSERT_STR_EQ(t.root->r->r->data, "c");

  ASSERT_PTR_NULL(t.root->r->r->r);
  ASSERT_PTR_NULL(t.root->r->r->l);

  bitree_destroy(&t);
}

TEST(remove_right_tree) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, NULL, "a"), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "c"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->r, "d"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "f"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "g"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->l, "h"), 0);

  bitree_remove_right(&t, NULL);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_PTR_NULL(t.root);

  bitree_destroy(&t);
}

TEST(remove_left_tree) {
  BiTree t;
  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, "a"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "b"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "c"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->l, "d"), 0);

  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "f"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "g"), 0);
  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->r, "h"), 0);

  bitree_remove_left(&t, NULL);

  ASSERT_INT_EQ(t.size, 0);
  ASSERT_PTR_NULL(t.root);

  bitree_destroy(&t);
}

// All traversals use the below tree.
/*
        20
       /  \
     09    53
    /  \     \
   05  15     79
       /
      11
*/
TEST(test_preorder_traversal) {
  BiTree t;
  char *expected[] = {"20", "09", "05", "15", "11", "53", "79"};
  List l;
  list_init(&l, NULL);

  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, "20"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "09"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "53"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "05"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->l, "15"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "79"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l->r, "11"), 0);

  bitree_preorder(t.root, &l);

  ASSERT_INT_EQ(l.size, 7);
  int i = 0;
  for (ListElement *e = l.head; e != NULL; e = e->next) {
    ASSERT_STR_EQ(e->data, expected[i]);
    ++i;
  }

  bitree_destroy(&t);
  list_destroy(&l);
}

TEST(test_inorder_traversal) {
  BiTree t;
  char *expected[] = {"05", "09", "11", "15", "20", "53", "79"};
  List l;
  list_init(&l, NULL);

  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, "20"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "09"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "53"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "05"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->l, "15"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "79"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l->r, "11"), 0);

  bitree_inorder(t.root, &l);

  ASSERT_INT_EQ(l.size, 7);
  int i = 0;
  for (ListElement *e = l.head; e != NULL; e = e->next) {
    ASSERT_STR_EQ(e->data, expected[i]);
    ++i;
  }

  bitree_destroy(&t);
  list_destroy(&l);
}

TEST(test_postorder_traversal) {
  BiTree t;
  char *expected[] = {"05", "11", "15", "09", "79", "53", "20"};
  List l;
  list_init(&l, NULL);

  ASSERT_INT_EQ(
      bitree_init(&t, (int (*)(const void *, const void *))strcmp, NULL), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, NULL, "20"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root, "09"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root, "53"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l, "05"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->l, "15"), 0);
  ASSERT_INT_EQ(bitree_insert_right(&t, t.root->r, "79"), 0);

  ASSERT_INT_EQ(bitree_insert_left(&t, t.root->l->r, "11"), 0);

  bitree_postorder(t.root, &l);

  ASSERT_INT_EQ(l.size, 7);
  int i = 0;
  for (ListElement *e = l.head; e != NULL; e = e->next) {
    ASSERT_STR_EQ(e->data, expected[i]);
    ++i;
  }

  bitree_destroy(&t);
  list_destroy(&l);
}

int main(void) {
  RUN_TEST(test_init);
  RUN_TEST(test_insert_left_root);
  RUN_TEST(test_insert_left_populated_root);
  RUN_TEST(test_insert_left_left);
  RUN_TEST(insert_left_not_leaf);
  RUN_TEST(test_remove_left_empty);
  RUN_TEST(test_remove_left_root_only);
  RUN_TEST(test_remove_left_leaf);
  RUN_TEST(test_remove_left_leaf_null);
  RUN_TEST(test_remove_left_branch);
  RUN_TEST(test_insert_right_root);
  RUN_TEST(test_insert_right_populated_root);
  RUN_TEST(test_insert_right_right);
  RUN_TEST(test_insert_right_not_leaf);
  RUN_TEST(insert_right_left_tree);
  RUN_TEST(test_remove_right_empty);
  RUN_TEST(test_remove_right_root_only);
  RUN_TEST(test_remove_right_leaf);
  RUN_TEST(test_remove_right_leaf_null);
  RUN_TEST(test_remove_right_branch);
  RUN_TEST(remove_right_tree);
  RUN_TEST(remove_left_tree);
  RUN_TEST(test_preorder_traversal);
  RUN_TEST(test_inorder_traversal);
  RUN_TEST(test_postorder_traversal);
  return 0;
}
