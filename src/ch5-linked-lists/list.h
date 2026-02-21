#ifndef LIST
#define LIST

#include <stdlib.h>

/**
 * The structure that describes an element of a list and its data
 */
typedef struct ListElement_ {
  void *data;
  struct ListElement_ *next;
} ListElement;

/**
 * The structure that defines the List (which contains ListElements)
 */
typedef struct List_ {
  /**
   * The number of elements in the List
   */
  int size;

  /**
   * Function that compares ListElements for equality.
   */
  int (*match)(const void *key, const void *key2);

  /**
   * Function that destroys a list element and its associated data
   */
  void (*destroy)(void *data);

  /**
   * The first element in the List.
   */
  ListElement *head;

  /**
   * The last element in the List.
   */
  ListElement *tail;

} List;

/**
 * @brief Initialises an empty List.
 *
 * @param list - An allocated pointer to a List structure.
 * @param destroy - The function used to free the dynamically allocated
 * data.
 */
void list_init(List *list, void (*destroy)(void *data));

/**
 * @brief Insert an element into the list after the element parameter.
 *
 * @param list - The list to insert the element into.
 * @param element - The element to insert the new element after.
 * @param data - The data to assign to the new elements data property.
 */
int list_insert_next(List *list, ListElement *element, void *data);

/**
 * @brief Removes an element from the list after the element parameter.
 * Provides the data from the element via the out parameter data.
 *
 * @param list - The list containing the element.
 * @param element - The element after which to remove the element.
 * @param data - Out parameter that will point to the removed element's
 * data attribute
 *
 * @returns int - 0 on success
 */
int list_remove_next(List *list, ListElement *element, void **data);

void list_destroy(List *list);
#endif
