#ifndef BITREE_H
#define BITREE_H
#include "../ch5-linked-lists/list.h"

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
void bitree_remove_left(BiTree *t, BiTreeNode *n);
void bitree_remove_right(BiTree *t, BiTreeNode *n);
void bitree_destroy(BiTree *t);
int bitree_preorder(BiTreeNode *n, List *l);
int bitree_inorder(BiTreeNode *n, List *l);
int bitree_postorder(BiTreeNode *n, List *l);
int bitree_eob(BiTreeNode *n);

#endif
