#include "dlist.h"
#include <stdlib.h>
#include <string.h>

void dlist_init(DList *list, void (*destroy)(void *data)) {
  memset(list, 0, sizeof(DList));
  list->destroy = destroy;
}

int dlist_insert_next(DList *list, DListElement *element, void *data) {
  DListElement *next = (DListElement *)malloc(sizeof(DListElement));
  next->data = data;
  next->next = NULL;
  next->previous = NULL;

  if (element == NULL) {
    if (list->size == 0) {
      list->head = next;
      list->tail = next;
    } else {
      next->next = list->head;
      list->head->previous = next;
      list->head = next;
    }
  } else {
    next->next = element->next;
    next->previous = element;

    if (element->next) {
      element->next->previous = next;
    } else {
      list->tail = next;
    }

    element->next = next;
  }

  ++list->size;

  return 0;
}

int dlist_insert_previous(DList *list, DListElement *element, void *data) {
  DListElement *previous = (DListElement *)malloc(sizeof(DListElement));
  previous->data = data;
  previous->next = NULL;
  previous->previous = NULL;

  if (element == NULL) {
    if (list->size == 0) {
      previous->next = NULL;
      previous->previous = NULL;
      list->head = previous;
      list->tail = previous;
    } else {
      list->tail->next = previous;
      previous->previous = list->tail;
      list->tail = previous;
    }
  } else {
    if (element == list->head) {
      previous->next = list->head;
      list->head->previous = previous;
      list->head = previous;
    } else {
      previous->next = element;
      previous->previous = element->previous;

      element->previous->next = previous;
      element->previous = previous;
    }
  }

  ++list->size;

  return 0;
}

int dlist_remove(DList *list, DListElement *element, void **data) {
  if (list->size == 0)
    return -1;

  *data = element->data;

  if (element->next) {
    element->next->previous = element->previous;

    if (list->head == element) {
      list->head = element->next;
    }
  }

  if (element->previous) {
    element->previous->next = element->next;

    if (list->tail == element) {
      list->tail = element->previous;
    }
  }

  free(element);
  --list->size;

  if (list->size == 0) {
    list->head = NULL;
    list->tail = NULL;
  }

  return 0;
}

void dlist_destroy(DList *list) {
  while (list->size > 0) {
    void *data;
    dlist_remove(list, list->head, &data);
    if (list->destroy) {
      list->destroy(data);
    }
  }
  memset(list, 0, sizeof(DList));
}
