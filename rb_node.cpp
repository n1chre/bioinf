//
// Created by Matija Orsolic on 28/12/2016.
//

#include "rb_node.h"

// Constructor
rb_node::rb_node() {
  left = NULL;
  right = NULL;
  parent = NULL;
  red = true;
}

// Getters and setters
uint64_t rb_node::get_symbol_count(char symbol) {
  return symbols[symbol];
}

void rb_node::increment_symbol_count(char symbol) {
  symbols[symbol]++;
}

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

uint64_t rb_node::get_block_number() const {
  return block_number;
}

void rb_node::set_block_number(uint64_t blockNumber) {
  rb_node::block_number = blockNumber;
}
