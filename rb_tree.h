//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBTREE_H
#define BIOINF_RBTREE_H

#include "rb_node.h"

class rb_tree {
 private:
  rb_node *root;

  static rb_node *rotate_right(rb_node *node);

  static rb_node *rotate_left(rb_node *node);

  void insert_fixup(rb_node *node);

  void insert_recursive(rb_node *root, rb_node *node);

 public:
  rb_tree();

  void insert(rb_node *node);

  rb_node *get_root() const;
  void set_root(rb_node *root);
};

#endif //BIOINF_RBTREE_H
