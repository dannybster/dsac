#ifndef SET_H
#define SET_H
#include "../ch5-linked-lists/list.h"

typedef List Set;
#define set_size(s) ((s)->size)
#define set_destroy list_destroy
void set_init(Set *set, void (*destroy)(void *),
              int (*match)(const void *, const void *));
int set_insert(Set *set, void *data);
int set_is_member(const Set *set, const void *data);
int set_remove(Set *set, const void *data);
int set_equal(const Set *s1, const Set *s2);
int set_union(const Set *s1, const Set *s2, Set *u);
int set_is_subset(const Set *s1, const Set *s2);
void set_difference(const Set *s1, const Set *s2, Set *d);
void set_intersection(const Set *s1, const Set *s2, Set *i);
#endif
