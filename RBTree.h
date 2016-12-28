//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBTREE_H
#define BIOINF_RBTREE_H

#include "RBNode.h"

class RBTree {
 private:
  RBNode *root;

  static RBNode *rotateRight(RBNode *node);

  static RBNode *rotateLeft(RBNode *node);

  void insertFixup(RBNode *node);

  void insertRecursive(RBNode *root, RBNode *node);

 public:
  RBTree();

  void insert(RBNode *node);

  RBNode *getRoot() const;
  void setRoot(RBNode *root);
};

#endif //BIOINF_RBTREE_H
