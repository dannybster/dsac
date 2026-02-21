#include "clist.h"
#include <stdlib.h>
#include <string.h>

void clist_init(CList *list, void (*destroy)(void *data)) {
  memset(list, 0, sizeof(CList));
  list->destroy = destroy;
}

void clist_destroy(CList *list) {
  while (list->size > 0) {
    void *data = NULL;
    clist_remove_next(list, list->head, &data);
    if (list->destroy) {
      list->destroy(data);
    }
  }
  memset(list, 0, sizeof(CList));
}

int clist_insert_next(CList *list, CListElement *element, void *data) {
  CListElement *next = NULL;
  if ((next = malloc(sizeof(CListElement))) == NULL) {
    return -1;
  }

  next->data = data;

  // Either insert at front or insert into empty list.
  if (element == NULL) {
    // Insert into empty list.
    if (list->size == 0) {
      next->next = next;
      list->head = next;
      list->tail = next;
    } else {
      // Insert at head.
      next->next = list->head;
      list->head = next;
      list->tail->next = list->head;
    }
  } else if (element == list->tail) {
    // Insert at tail.
    element->next = next;
    list->tail = next;
    list->tail->next = list->head;
  } else {
    // Insert somewhere in the middle.
    next->next = element->next;
    element->next = next;
  }

  list->size += 1;
  return 0;
}

void clist_remove_next(CList *list, CListElement *element, void **data) {
  CListElement *remove = NULL;

  if (element == NULL || element == list->tail) {
    // Remove head.
    remove = list->head;
    list->head = remove->next;
    list->tail->next = list->head;
  } else if (element->next == list->tail) {
    remove = list->tail;
    list->tail = element;
    element->next = list->head;
  } else {
    remove = element->next;
    element->next = remove->next;
  }

  *data = remove->data;
  --list->size;

  if (list->size == 0) {
    list->head = NULL;
    list->tail = NULL;
  }

  free(remove);
}
