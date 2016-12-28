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
  uint64_t block_number;
  std::map<char, uint64_t> symbols;

 public:
  rb_node();

  uint64_t get_symbol_count(char symbol);
  void increment_symbol_count(char symbol);

  rb_node *get_left() const;
  void set_left(rb_node *left);
  rb_node *get_right() const;
  void set_right(rb_node *right);
  rb_node *get_parent() const;
  void set_parent(rb_node *parent);
  bool is_red() const;
  void set_red(bool isRed);
  uint64_t get_block_number() const;
  void set_block_number(uint64_t blockNumber);
};

#endif //BIOINF_RBNODE_H
