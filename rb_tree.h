//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBTREE_H
#define BIOINF_RBTREE_H

#include <vector>

#include "rb_node.h"
#include "data.h"
#include "rank_select.h"

class rb_tree : public rank_select {
 private:
  rb_node *root;

  static rb_node *rotate_right(rb_node *node);
  static rb_node *rotate_left(rb_node *node);
  void insert_fixup(rb_node *node);
  rb_node *insert_recursive(data *d, rb_node *node, rb_node *new_node);

 public:
  rb_tree(std::vector<data *> &nodes);

  void insert(data *d);
  rb_node *get_root() const;
  void set_root(rb_node *root);
  const uint32_t rank(char i, uint32_t idx) const override;
  const uint32_t select(char i, uint32_t idx) const override;
};

#endif //BIOINF_RBTREE_H
