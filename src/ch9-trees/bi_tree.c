#include "bi_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void bitree_remove_left(BiTree *t, BiTreeNode *n) {
  BiTreeNode **remove = NULL;

  if (t->size == 0)
    return;

  if (n == NULL)
    remove = &t->root;
  else
    remove = &n->l;

  if (*remove != NULL) {
    bitree_remove_left(t, *remove);
    bitree_remove_right(t, *remove);

    if (t->destroy != NULL)
      t->destroy((*remove)->data);

    free(*remove);
    *remove = NULL;
    t->size -= 1;
  }
}

void bitree_remove_right(BiTree *t, BiTreeNode *n) {
  BiTreeNode **remove = NULL;

  if (t->size == 0)
    return;

  if (n == NULL)
    remove = &t->root;
  else
    remove = &n->r;

  if (*remove) {
    bitree_remove_right(t, *remove);
    bitree_remove_left(t, *remove);

    if (t->destroy)
      t->destroy((*remove)->data);

    free(*remove);
    *remove = NULL;
    t->size--;
  }
}

int bitree_eob(BiTreeNode *n) {
  if (n == NULL)
    return 1;
  return 0;
}

int bitree_preorder(BiTreeNode *n, List *l) {
  if (!bitree_eob(n)) {
    if (list_insert_next(l, l->tail, n->data) != 0)
      return -1;

    if (!bitree_eob(n->l))
      if (bitree_preorder(n->l, l) != 0)
        return -1;

    if (!bitree_eob(n->r))
      if (bitree_preorder(n->r, l) != 0)
        return -1;
  }

  return 0;
}

int bitree_inorder(BiTreeNode *n, List *l) {
  if (!bitree_eob(n)) {
    if (!bitree_eob(n->l))
      if (bitree_inorder(n->l, l) != 0)
        return -1;

    if (list_insert_next(l, l->tail, n->data) != 0)
      return -1;

    if (!bitree_eob(n->r))
      if (bitree_inorder(n->r, l) != 0)
        return -1;
  }

  return 0;
}

int bitree_postorder(BiTreeNode *n, List *l) {
  if (!bitree_eob(n)) {
    if (!bitree_eob(n->l))
      if (bitree_postorder(n->l, l) != 0)
        return -1;

    if (!bitree_eob(n->r))
      if (bitree_postorder(n->r, l) != 0)
        return -1;

    if (list_insert_next(l, l->tail, n->data) != 0)
      return -1;
  }

  return 0;
}

void bitree_destroy(BiTree *t) {
  bitree_remove_left(t, NULL);
  memset(t, 0, sizeof(BiTree));
}
