//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBNODE_H
#define BIOINF_RBNODE_H

#include "data.h"

/**
 * Node for the red black tree.
 */
class rb_node {
 private:
  rb_node *right;
  rb_node *left;
  rb_node *parent;
  bool red;
  data *d;

 public:
  /**
   * Constructor.
   * @param d   node data
   * @param red true if node is red
   */
  rb_node(data *d, bool red = true);

  // Getters and setters
  rb_node *get_left() const;
  void set_left(rb_node *left);
  rb_node *get_right() const;
  void set_right(rb_node *right);
  rb_node *get_parent() const;
  void set_parent(rb_node *parent);
  bool is_red() const;
  void set_red(bool isRed);
  data *get_d() const;
};

#endif //BIOINF_RBNODE_H
