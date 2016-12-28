//
// Created by Matija Orsolic on 28/12/2016.
//

#include "rb_tree.h"

// Constructor
rb_tree::rb_tree() {
  root = NULL;
}

// Public functions
void rb_tree::insert(rb_node *node) {
  insertRecursive(root, node);
  insertFixup(node);
}

// Private functions
void rb_tree::insertRecursive(rb_node *root, rb_node *node) {
  if (root == NULL) {
    root = node;
    return;
  }

  if (root->getBlockNumber() > node->getBlockNumber()) {
    insertRecursive(root->getRight(), node);
  } else {
    insertRecursive(root->getLeft(), node);
  }
}

void rb_tree::insertFixup(rb_node *node) {
  while (node->getParent()->isRed()) {
    rb_node *parent = node->getParent();
    rb_node *grandparent = parent->getParent();

    if (parent == grandparent->getLeft()) {
      rb_node *uncle = grandparent->getRight();

      if (uncle->isRed()) {
        parent->setRed(false);
        uncle->setRed(false);
        grandparent->setRed(true);
        node = grandparent;
      } else {
        if (node == node->getParent()->getRight()) {
          rotateLeft(node);
          node = parent;
        }
        rotateRight(parent);
        parent->setRed(false);
        grandparent->setRed(true);
      }
    } else {
      rb_node *uncle = grandparent->getLeft();

      if (uncle->isRed()) {
        parent->setRed(false);
        uncle->setRed(false);
        grandparent->setRed(true);
        node = grandparent;
      } else {
        if (node == node->getParent()->getLeft()) {
          rotateRight(node);
          node = parent;
        }
        rotateLeft(parent);
        parent->setRed(false);
        grandparent->setRed(true);
      }
    }
  }

  root->setRed(false);
}

rb_node *rb_tree::rotateLeft(rb_node *node) {
  return nullptr;
}

rb_node *rb_tree::rotateRight(rb_node *node) {
  return nullptr;
}

// Getters and setters
rb_node *rb_tree::getRoot() const {
  return root;
}

void rb_tree::setRoot(rb_node *root) {
  rb_tree::root = root;
}
