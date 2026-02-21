typedef struct CListElement_ {
  void *data;
  struct CListElement_ *next;
} CListElement;

typedef struct CList_ {
  int size;
  void (*destroy)(void *data);
  CListElement *head;
  CListElement *tail;
} CList;

void clist_init(CList *list, void (*destroy)(void *data));
void clist_destroy(CList *list);
int clist_insert_next(CList *list, CListElement *element, void *data);
void clist_remove_next(CList *list, CListElement *element, void **data);
