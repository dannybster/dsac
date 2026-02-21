#include "list.h"
#include <string.h>

void list_init(List *list, void (*destroy)(void *data)) {
  memset(list, 0, sizeof(List));
  list->destroy = destroy;
}

int list_insert_next(List *list, ListElement *element, void *data) {
  ListElement *new_element = NULL;

  if ((new_element = malloc(sizeof(ListElement))) == NULL) {
    return -1;
  }

  new_element->data = data;

  // Insert at the beginning.
  if (element == NULL) {
    // If the list is empty then the head is also the tail.
    if (list->size == 0) {
      list->tail = new_element;
    }

    // The head is now the new element
    new_element->next = list->head;
    list->head = new_element;
  } else {
    // We are inserting a new tail.
    if (element == list->tail) {
      list->tail = new_element;
    }

    new_element->next = element->next;
    element->next = new_element;
  }

  // We always grow by one.
  ++list->size;
  return 0;
}

int list_remove_next(List *list, ListElement *element, void **data) {
  if (list->size == 0) {
    return -1;
  }

  ListElement *remove;

  if (element == NULL) {
    remove = list->head;
    list->head = remove->next;
    if (list->size == 1) {
      list->tail = NULL;
    }
  } else {
    remove = element->next;
    if (remove == NULL) {
      return -1;
    }

    element->next = remove->next;

    if (element->next == NULL) {
      list->tail = element;
    }
  }

  *data = remove->data;
  free(remove);
  --list->size;
  return 0;
}

void list_destroy(List *list) {
  ListElement *element = list->head;
  while (element) {
    if (list->destroy) {
      list->destroy(element->data);
    }
    ListElement *next = element->next;
    free(element);
    element = next;
  }
  memset(list, 0, sizeof(List));
}
