//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBTREE_H
#define BIOINF_RBTREE_H

#include <vector>

#include "rb_node.h"
#include "data.h"
#include "rank_select.h"

/**
 * Implementation of rank select using the red black tree.
 */
class rb_tree : public rank_select {
 private:
  rb_node *root;
  uint32_t word_size;

  /*
   * Right rotates node around it's parent.
   */
  void rotate_right(rb_node *node);

  /*
   * Left rotates node around it's parent.
   */
  void rotate_left(rb_node *node);

  /*
   * Balances the red black tree after the insertion od the node.
   */
  void insert_fixup(rb_node *node);

  /*
   * Recursively inserts new_node into the balanced tree.
   */
  rb_node *insert_recursive(rb_node *node, rb_node *new_node);

  /*
   * Returns the node containing the data between idx and idx + word_size.
   */
  const rb_node *find_by_index(rb_node *node, uint32_t idx) const;

  /*
   * Returns the node containing the data with the idx-th character i.
   */
  const rb_node *find_by_count(rb_node *node, char i, uint32_t idx) const;

 public:
  /**
   * Constructor. Creates the tree and inserts the given nodes in it.
   *
   * @param nodes       vector of the data to be inserted into the tree
   * @param word_size   word size of one node
   */
  rb_tree(std::vector<data *> &nodes, uint32_t word_size);

  /**
   * Inserts the data d into the tree.
   *
   * @param d   data
   */
  void insert(data *d);

  const char operator[](const uint32_t idx) const override;
  const uint32_t rank(char i, uint32_t idx) const override;
  const uint32_t select(char i, uint32_t idx) const override;
};

#endif //BIOINF_RBTREE_H
