#include "bi_tree.h"
#include <stdlib.h>

int bitree_init(BiTree *t, int (*match)(const void *, const void *),
                void (*destroy)(void *)) {

  t->size = 0;
  t->root = NULL;
  t->match = match;
  t->destroy = destroy;

  return 0;
}

int bitree_insert_left(BiTree *t, BiTreeNode *prev, void *data) {
  // Are we trying to insert at the root of a populated tree?
  if (t->root != NULL && prev == NULL)
    return 1;

  // Are we trying to insert to the left of a non-leaf node?
  if (prev && prev->l != NULL)
    return 1;

  BiTreeNode *n;
  if ((n = calloc(1, sizeof(BiTreeNode))) == NULL)
    return 1;

  n->data = data;

  if (prev == NULL)
    t->root = n;
  else
    prev->l = n;

  t->size += 1;
  return 0;
}

int bitree_insert_right(BiTree *t, BiTreeNode *prev, void *data) {
  // Are we trying to insert at the root of a populated tree?
  if (t->root != NULL && prev == NULL)
    return 1;

  // Are we trying to insert to the right of a non-leaf node?
  if (prev && prev->r != NULL)
    return 1;

  BiTreeNode *n;
  if ((n = calloc(1, sizeof(BiTreeNode))) == NULL)
    return 1;

  n->data = data;

  if (prev == NULL)
    t->root = n;
  else
    prev->r = n;

  t->size += 1;
  return 0;
}

void bitree_destroy(BiTree *t) {}
