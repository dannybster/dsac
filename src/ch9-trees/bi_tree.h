#ifndef BITREE_H
#define BITREE_H
typedef struct BiTreeNode_ {
  void *data;
  struct BiTreeNode_ *l;
  struct BiTreeNode_ *r;
} BiTreeNode;

typedef struct BiTree_ {
  BiTreeNode *root;
  int size;
  int (*match)(const void *, const void *);
  void (*destroy)(void *data);
} BiTree;

int bitree_init(BiTree *t, int (*match)(const void *, const void *),
                void (*destroy)(void *));
int bitree_insert_left(BiTree *t, BiTreeNode *prev, void *data);
int bitree_insert_right(BiTree *t, BiTreeNode *prev, void *data);
void bitree_destroy(BiTree *t);
#endif
