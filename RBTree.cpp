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
