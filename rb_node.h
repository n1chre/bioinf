//
// Created by Matija Orsolic on 28/12/2016.
//

#ifndef BIOINF_RBNODE_H
#define BIOINF_RBNODE_H

#include <map>

class rb_node {
 private:
  rb_node *right;
  rb_node *left;
  rb_node *parent;
  bool red;
  uint64_t blockNumber;
  std::map<char, uint64_t> symbols;

 public:
  rb_node();

  uint64_t getSymbolCount(char symbol);
  void incrementSymbolCount(char symbol);

  rb_node *getLeft() const;
  void setLeft(rb_node *left);
  rb_node *getRight() const;
  void setRight(rb_node *right);
  rb_node *getParent() const;
  void setParent(rb_node *parent);
  bool isRed() const;
  void setRed(bool isRed);
  uint64_t getBlockNumber() const;
  void setBlockNumber(uint64_t blockNumber);
};

#endif //BIOINF_RBNODE_H
