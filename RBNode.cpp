//
// Created by Matija Orsolic on 28/12/2016.
//

#include "RBNode.h"

// Constructor
RBNode::RBNode() {
  left = NULL;
  right = NULL;
  parent = NULL;
  red = true;
}

// Getters and setters
uint64_t RBNode::getSymbolCount(char symbol) {
  return symbols[symbol];
}

void RBNode::incrementSymbolCount(char symbol) {
  symbols[symbol]++;
}

RBNode *RBNode::getLeft() const {
  return left;
}

void RBNode::setLeft(RBNode *left) {
  RBNode::left = left;
}

RBNode *RBNode::getRight() const {
  return right;
}

void RBNode::setRight(RBNode *right) {
  RBNode::right = right;
}

RBNode *RBNode::getParent() const {
  return parent;
}

void RBNode::setParent(RBNode *parent) {
  RBNode::parent = parent;
}

bool RBNode::isRed() const {
  return red;
}

void RBNode::setRed(bool red) {
  RBNode::red = red;
}

uint64_t RBNode::getBlockNumber() const {
  return blockNumber;
}

void RBNode::setBlockNumber(uint64_t blockNumber) {
  RBNode::blockNumber = blockNumber;
}
