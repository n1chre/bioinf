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
uint64_t rb_node::getSymbolCount(char symbol) {
  return symbols[symbol];
}

void rb_node::incrementSymbolCount(char symbol) {
  symbols[symbol]++;
}

rb_node *rb_node::getLeft() const {
  return left;
}

void rb_node::setLeft(rb_node *left) {
  rb_node::left = left;
}

rb_node *rb_node::getRight() const {
  return right;
}

void rb_node::setRight(rb_node *right) {
  rb_node::right = right;
}

rb_node *rb_node::getParent() const {
  return parent;
}

void rb_node::setParent(rb_node *parent) {
  rb_node::parent = parent;
}

bool rb_node::isRed() const {
  return red;
}

void rb_node::setRed(bool red) {
  rb_node::red = red;
}

uint64_t rb_node::getBlockNumber() const {
  return blockNumber;
}

void rb_node::setBlockNumber(uint64_t blockNumber) {
  rb_node::blockNumber = blockNumber;
}
