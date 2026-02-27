#include "../test_helpers.h"
#include "set.h"

TEST(test_init) {
  Set set;
  set_init(&set, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_size(&set), 0);

  set_destroy(&set);
}

TEST(test_insert_unique) {
  Set set;
  set_init(&set, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set, "c"), 0);

  ASSERT_INT_EQ(set_size(&set), 3);

  set_destroy(&set);
}

TEST(test_insert_duplicate) {
  Set set;
  set_init(&set, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set, "c"), 0);
  ASSERT_INT_EQ(set_insert(&set, "c"), 1);

  ASSERT_INT_EQ(set_size(&set), 3);

  set_destroy(&set);
}

TEST(test_is_member) {
  Set set;
  set_init(&set, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set, "c"), 0);

  ASSERT_INT_EQ(set_is_member(&set, "a"), 1);
  ASSERT_INT_EQ(set_is_member(&set, "b"), 1);
  ASSERT_INT_EQ(set_is_member(&set, "c"), 1);

  set_destroy(&set);
}

TEST(test_is_not_member) {
  Set set;
  set_init(&set, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set, "c"), 0);

  ASSERT_INT_EQ(set_is_member(&set, "aa"), 0);

  set_destroy(&set);
}

TEST(test_remove_nonexisting_item) {
  Set set;
  set_init(&set, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set, "c"), 0);

  ASSERT_INT_EQ(set_remove(&set, "aa"), -1);
  ASSERT_INT_EQ(set_size(&set), 3);

  set_destroy(&set);
}

TEST(test_remove_existing_item) {
  Set set;
  set_init(&set, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set, "c"), 0);

  ASSERT_INT_EQ(set_remove(&set, "b"), 0);
  ASSERT_INT_EQ(set_size(&set), 2);
  ASSERT_INT_EQ(set_is_member(&set, "b"), 0);

  set_destroy(&set);
}

TEST(test_set_is_equal) {
  Set set1, set2;
  set_init(&set1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&set2, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set1, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set1, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set1, "c"), 0);

  ASSERT_INT_EQ(set_insert(&set2, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set2, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set2, "c"), 0);

  ASSERT_INT_EQ(set_equal(&set1, &set2), 1);

  set_destroy(&set1);
  set_destroy(&set2);
}

TEST(test_set_not_equal_different_members) {
  Set set1, set2;
  set_init(&set1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&set2, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set1, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set1, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set1, "c"), 0);

  ASSERT_INT_EQ(set_insert(&set2, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set2, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set2, "d"), 0);

  ASSERT_INT_EQ(set_equal(&set1, &set2), 0);

  set_destroy(&set1);
  set_destroy(&set2);
}

TEST(test_set_equal_is_subset_superset) {
  Set set1, set2;
  set_init(&set1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&set2, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&set1, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set1, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set1, "c"), 0);

  ASSERT_INT_EQ(set_insert(&set2, "a"), 0);
  ASSERT_INT_EQ(set_insert(&set2, "b"), 0);
  ASSERT_INT_EQ(set_insert(&set2, "c"), 0);
  ASSERT_INT_EQ(set_insert(&set2, "d"), 0);

  ASSERT_INT_EQ(set_equal(&set1, &set2), 0);
  ASSERT_INT_EQ(set_equal(&set2, &set1), 0);

  set_destroy(&set1);
  set_destroy(&set2);
}

TEST(test_union_empty) {
  Set s1, s2, u;
  set_init(&s1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&s2, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&u, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_union(&s1, &s2, &u), 0);
  ASSERT_INT_EQ(set_size(&u), 0);

  set_destroy(&s1);
  set_destroy(&s2);
  set_destroy(&u);
}

TEST(test_union) {
  Set s1, s2, u, expected;
  set_init(&s1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&s2, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&u, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&expected, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&s1, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "b"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "c"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "d"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "e"), 0);

  ASSERT_INT_EQ(set_insert(&s2, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "b"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "c"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "d"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "f"), 0);

  ASSERT_INT_EQ(set_insert(&expected, "a"), 0);
  ASSERT_INT_EQ(set_insert(&expected, "b"), 0);
  ASSERT_INT_EQ(set_insert(&expected, "c"), 0);
  ASSERT_INT_EQ(set_insert(&expected, "d"), 0);
  ASSERT_INT_EQ(set_insert(&expected, "e"), 0);
  ASSERT_INT_EQ(set_insert(&expected, "f"), 0);

  ASSERT_INT_EQ(set_union(&s1, &s2, &u), 0);

  ASSERT_INT_EQ(set_equal(&u, &expected), 1);

  set_destroy(&s1);
  set_destroy(&s2);
  set_destroy(&expected);
  set_destroy(&u);
}

TEST(test_not_is_subset) {
  Set s1, s2;
  set_init(&s1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&s2, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&s1, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "b"), 0);

  ASSERT_INT_EQ(set_insert(&s2, "1"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "2"), 0);

  ASSERT_INT_EQ(set_is_subset(&s1, &s2), 0);

  set_destroy(&s1);
  set_destroy(&s2);
}

TEST(test_is_subset) {
  Set s1, s2;
  set_init(&s1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&s2, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&s1, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "b"), 0);

  ASSERT_INT_EQ(set_insert(&s2, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "b"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "1"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "2"), 0);

  ASSERT_INT_EQ(set_is_subset(&s1, &s2), 1);
  ASSERT_INT_EQ(set_is_subset(&s2, &s1), 0);

  set_destroy(&s1);
  set_destroy(&s2);
}

TEST(test_difference) {
  Set s1, s2, d, expected;
  set_init(&s1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&s2, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&d, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&expected, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&s1, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "b"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "1"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "2"), 0);

  ASSERT_INT_EQ(set_insert(&s2, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "b"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "z"), 0);

  ASSERT_INT_EQ(set_insert(&expected, "1"), 0);
  ASSERT_INT_EQ(set_insert(&expected, "2"), 0);

  set_difference(&s1, &s2, &d);

  ASSERT_INT_EQ(set_equal(&d, &expected), 1);

  set_destroy(&s1);
  set_destroy(&s2);
  set_destroy(&d);
  set_destroy(&expected);
}

TEST(test_intersection) {
  Set s1, s2, i, expected;
  set_init(&s1, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&s2, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&i, NULL, (int (*)(const void *, const void *))strcmp);
  set_init(&expected, NULL, (int (*)(const void *, const void *))strcmp);

  ASSERT_INT_EQ(set_insert(&s1, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "b"), 0);
  ASSERT_INT_EQ(set_insert(&s1, "1"), 0);

  ASSERT_INT_EQ(set_insert(&s2, "a"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "b"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "2"), 0);
  ASSERT_INT_EQ(set_insert(&s2, "z"), 0);

  ASSERT_INT_EQ(set_insert(&expected, "a"), 0);
  ASSERT_INT_EQ(set_insert(&expected, "b"), 0);

  set_intersection(&s1, &s2, &i);

  ASSERT_INT_EQ(set_equal(&i, &expected), 1);

  set_destroy(&s1);
  set_destroy(&s2);
  set_destroy(&i);
  set_destroy(&expected);
}

int main(void) {
  RUN_TEST(test_init);
  RUN_TEST(test_insert_unique);
  RUN_TEST(test_is_member);
  RUN_TEST(test_is_not_member);
  RUN_TEST(test_insert_duplicate);
  RUN_TEST(test_remove_nonexisting_item);
  RUN_TEST(test_remove_existing_item);
  RUN_TEST(test_set_is_equal);
  RUN_TEST(test_set_not_equal_different_members);
  RUN_TEST(test_set_equal_is_subset_superset);
  RUN_TEST(test_union_empty);
  RUN_TEST(test_union);
  RUN_TEST(test_not_is_subset);
  RUN_TEST(test_is_subset);
  RUN_TEST(test_difference);
  RUN_TEST(test_intersection);
  return 0;
}
