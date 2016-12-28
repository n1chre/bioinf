//
// Created by Matija Orsolic on 28/12/2016.
//

#include "RBTree.h"

// Constructor
RBTree::RBTree() {
  root = NULL;
}

// Public functions
void RBTree::insert(RBNode *node) {
  insertRecursive(root, node);
  insertFixup(node);
}

// Private functions
void RBTree::insertRecursive(RBNode *root, RBNode *node) {
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

void RBTree::insertFixup(RBNode *node) {
  while (node->getParent()->isRed()) {
    RBNode *parent = node->getParent();
    RBNode *grandparent = parent->getParent();

    if (parent == grandparent->getLeft()) {
      RBNode *uncle = grandparent->getRight();

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
      RBNode *uncle = grandparent->getLeft();

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

RBNode *RBTree::rotateLeft(RBNode *node) {
  return nullptr;
}

RBNode *RBTree::rotateRight(RBNode *node) {
  return nullptr;
}

// Getters and setters
RBNode *RBTree::getRoot() const {
  return root;
}

void RBTree::setRoot(RBNode *root) {
  RBTree::root = root;
}
