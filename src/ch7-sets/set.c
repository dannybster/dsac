#include "set.h"

void set_init(Set *set, void (*destroy)(void *),
              int (*match)(const void *, const void *)) {
  list_init(set, destroy);
  set->match = match;
}

int set_insert(Set *set, void *data) {
  if (set_is_member(set, data) == 1) {
    return 1;
  }
  return list_insert_next(set, set->head, data);
}

int set_is_member(const Set *set, const void *data) {
  ListElement *item = set->head;
  while (item != NULL) {
    if (set->match(data, item->data) == 0) {
      return 1;
    }
    item = item->next;
  }
  return 0;
}

int set_remove(Set *set, const void *data) {
  ListElement *member, *previous = NULL;

  for (member = set->head; member != NULL; member = member->next) {
    if (set->match(data, member->data) == 0)
      break;

    previous = member;
  }

  if (member == NULL)
    return -1;

  void *removed;
  return list_remove_next(set, previous, &removed);
}

int set_equal(const Set *s1, const Set *s2) {
  if (set_size(s1) != set_size(s2)) {
    return 0;
  }

  ListElement *element = NULL;

  for (element = s1->head; element != NULL; element = element->next) {
    if (set_is_member(s2, element->data) == 0) {
      return 0;
    }
  }
  return 1;
}

int set_union(const Set *s1, const Set *s2, Set *u) {
  for (ListElement *element = s1->head; element != NULL;
       element = element->next) {
    set_insert(u, element->data);
  }

  for (ListElement *element = s2->head; element != NULL;
       element = element->next) {
    set_insert(u, element->data);
  }

  return 0;
}

int set_is_subset(const Set *s1, const Set *s2) {
  for (ListElement *element = s1->head; element != NULL;
       element = element->next) {
    if (set_is_member(s2, element->data) == 0)
      return 0;
  }
  return 1;
}

void set_difference(const Set *s1, const Set *s2, Set *d) {
  for (ListElement *e = s1->head; e != NULL; e = e->next) {
    if (set_is_member(s2, e->data) == 0) {
      set_insert(d, e->data);
    }
  }
}

void set_intersection(const Set *s1, const Set *s2, Set *i) {
  for (ListElement *e = s1->head; e != NULL; e = e->next) {
    if (set_is_member(s2, e->data) == 1) {
      set_insert(i, e->data);
    }
  }
}
