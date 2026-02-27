#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST(name) static void name(void)
#define RUN_TEST(name)                                                         \
  printf("  %s... ", #name);                                                   \
  name();                                                                      \
  printf("passed\n")

#define ASSERT_INT_EQ(a, b)                                                    \
  do {                                                                         \
    int _a = (a), _b = (b);                                                    \
    if (_a != _b) {                                                            \
      printf("FAIL: %s == %s (got %d, expected %d)\n", #a, #b, _a, _b);        \
      abort();                                                                 \
    }                                                                          \
  } while (0)

#define ASSERT_STR_EQ(a, b)                                                    \
  do {                                                                         \
    const char *_a = (a), *_b = (b);                                           \
    if (strcmp(_a, _b) != 0) {                                                 \
      printf("FAIL: %s == %s (got \"%s\", expected \"%s\")\n", #a, #b, _a,     \
             _b);                                                              \
      abort();                                                                 \
    }                                                                          \
  } while (0)

#define ASSERT_PTR_NULL(a)                                                     \
  do {                                                                         \
    if ((a) != NULL) {                                                         \
      printf("FAIL: %s expected NULL (got %p)\n", #a, (void *)(a));            \
      abort();                                                                 \
    }                                                                          \
  } while (0)

#define ASSERT_PTR_NOT_NULL(a)                                                 \
  do {                                                                         \
    if ((a) == NULL) {                                                         \
      printf("FAIL: %s expected not NULL\n", #a);                              \
      abort();                                                                 \
    }                                                                          \
  } while (0)

#define ASSERT_PTR_EQ(a, b)                                                    \
  do {                                                                         \
    const void *_a = (void *)(a), *_b = (void *)(b);                           \
    if (_a != _b) {                                                            \
      printf("FAIL: %s == %s (got %p, expected %p)\n", #a, #b, _a, _b);        \
      abort();                                                                 \
    }                                                                          \
  } while (0)
