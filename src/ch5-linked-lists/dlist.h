typedef struct DListElement_ {
  void *data;
  struct DListElement_ *next;
  struct DListElement_ *previous;
} DListElement;

typedef struct DList_ {
  int size;
  void (*destroy)(void *data);
  DListElement *head;
  DListElement *tail;
} DList;

void dlist_init(DList *list, void (*destroy)(void *data));
int dlist_insert_next(DList *list, DListElement *element, void *data);
int dlist_insert_previous(DList *list, DListElement *element, void *data);
int dlist_remove(DList *list, DListElement *element, void **data);
void dlist_destroy(DList *list);
