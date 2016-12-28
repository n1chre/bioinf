//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBNODE_H
#define BIOINF_RBNODE_H

#include <map>

class RBNode {
 private:
  RBNode *right;
  RBNode *left;
  RBNode *parent;
  bool red;
  uint64_t blockNumber;
  std::map<char, uint64_t> symbols;

 public:
  RBNode();

  uint64_t getSymbolCount(char symbol);
  void incrementSymbolCount(char symbol);

  RBNode *getLeft() const;
  void setLeft(RBNode *left);
  RBNode *getRight() const;
  void setRight(RBNode *right);
  RBNode *getParent() const;
  void setParent(RBNode *parent);
  bool isRed() const;
  void setRed(bool isRed);
  uint64_t getBlockNumber() const;
  void setBlockNumber(uint64_t blockNumber);
};

#endif //BIOINF_RBNODE_H
