//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBNODE_H
#define BIOINF_RBNODE_H

#include "data.h"

class rb_node {
 private:
  rb_node *right;
  rb_node *left;
  rb_node *parent;
  bool red;
  data *d;

 public:
  rb_node(data *d, bool red = true);

  rb_node *get_left() const;
  void set_left(rb_node *left);
  rb_node *get_right() const;
  void set_right(rb_node *right);
  rb_node *get_parent() const;
  void set_parent(rb_node *parent);
  bool is_red() const;
  void set_red(bool isRed);
  data *get_d() const;
  void set_d(data *d);
};

#endif //BIOINF_RBNODE_H
