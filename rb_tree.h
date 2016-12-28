//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBTREE_H
#define BIOINF_RBTREE_H

#include "rb_node.h"

class rb_tree {
 private:
  rb_node *root;

  static rb_node *rotateRight(rb_node *node);

  static rb_node *rotateLeft(rb_node *node);

  void insertFixup(rb_node *node);

  void insertRecursive(rb_node *root, rb_node *node);

 public:
  rb_tree();

  void insert(rb_node *node);

  rb_node *getRoot() const;
  void setRoot(rb_node *root);
};

#endif //BIOINF_RBTREE_H
