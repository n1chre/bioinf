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

  void rotate_right(rb_node *node);
  void rotate_left(rb_node *node);
  void insert_fixup(rb_node *node);
  rb_node *insert_recursive(data *d, rb_node *node, rb_node *new_node);
  const rb_node *find_by_index(rb_node *node, uint32_t idx) const;
  const rb_node *find_by_count(rb_node *node, char i, uint32_t idx) const;

 public:
  rb_tree(std::vector<data *> &nodes);
  void insert(data *d);

  const char operator[](const uint32_t idx) const override;
  const uint32_t rank(char i, uint32_t idx) const override;
  const uint32_t select(char i, uint32_t idx) const override;
};

#endif //BIOINF_RBTREE_H
