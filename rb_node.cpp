//
// Created by Matija Orsolic on 28/12/2016.
//

#include "rb_node.h"

// Constructor
rb_node::rb_node(data *d, bool red) : d(d), red(red) {
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

// Getters and setters
rb_node *rb_node::get_left() const {
  return left;
}

void rb_node::set_left(rb_node *left) {
  rb_node::left = left;
}

rb_node *rb_node::get_right() const {
  return right;
}

void rb_node::set_right(rb_node *right) {
  rb_node::right = right;
}

rb_node *rb_node::get_parent() const {
  return parent;
}

void rb_node::set_parent(rb_node *parent) {
  rb_node::parent = parent;
}

bool rb_node::is_red() const {
  return red;
}

void rb_node::set_red(bool red) {
  rb_node::red = red;
}

data *rb_node::get_d() const {
  return d;
}

void rb_node::set_d(data *d) {
  rb_node::d = d;
}
