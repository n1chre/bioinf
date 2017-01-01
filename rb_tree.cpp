//
// Created by Matija Orsolic on 28/12/2016.
//

#include "rb_tree.h"

// Constructor
rb_tree::rb_tree(std::vector<data *> &nodes, uint32_t word_size) : word_size(word_size) {
  root = nullptr;
  for (auto i : nodes) {
    insert(i);
  }
}

// Public functions
void rb_tree::insert(data *d) {
  rb_node *node = new rb_node(d);
  root = insert_recursive(d, root, node);
  insert_fixup(node);
}

const char rb_tree::operator[](const uint32_t idx) const {
  auto node = find_by_index(root, idx);
  if (node==nullptr) {
    throw std::out_of_range("Index out of bounds");
  }
  auto d = node->get_d();
  return (*d->get_wave())[idx - d->get_starting_idx()];
}

const uint32_t rb_tree::rank(char i, uint32_t idx) const {
  const rb_node *node = find_by_index(root, idx);
  if (node==nullptr) {
    throw std::out_of_range("Index out of bounds");
  }
  data *d = node->get_d();
  return d->get_count(i) + d->get_wave()->rank(i, idx - d->get_starting_idx());
}

const uint32_t rb_tree::select(char i, uint32_t idx) const {
  const rb_node *node = find_by_count(root, i, idx);
  if (node==nullptr) {
    throw std::out_of_range("Index out of bounds");
  }
  data *d = node->get_d();
  return d->get_starting_idx() + d->get_wave()->select(i, idx - d->get_count(i));
}

// Private functions
rb_node *rb_tree::insert_recursive(data *d, rb_node *node, rb_node *new_node) {
  if (node==nullptr) {
    node = new_node;
  } else {
    new_node->set_parent(node);
    if (d->get_starting_idx() > node->get_d()->get_starting_idx()) {
      node->set_right(insert_recursive(d, node->get_right(), new_node));
    } else {
      node->set_left(insert_recursive(d, node->get_left(), new_node));
    }
  }
  return node;
}

const rb_node *rb_tree::find_by_index(rb_node *node, uint32_t idx) const {
  if (node==nullptr) {
    return nullptr;
  }

  if (idx < node->get_d()->get_starting_idx()) {
    return find_by_index(node->get_left(), idx);
  }
  if (idx > node->get_d()->get_starting_idx() + node->get_d()->get_wave()->length()) {
    return find_by_index(node->get_right(), idx);
  }
  return node;
}

const rb_node *rb_tree::find_by_count(rb_node *node, char i, uint32_t idx) const {
  if (node==nullptr) {
    return nullptr;
  }

  uint32_t count = node->get_d()->get_count(i);
  if (idx <= count) {
    return find_by_count(node->get_left(), i, idx);
  }
  if (idx > count + node->get_d()->get_wave()->rank(i, word_size - 1)) {
    return find_by_count(node->get_right(), i, idx);
  }
  return node;
}

void rb_tree::insert_fixup(rb_node *node) {
  rb_node *parent = node->get_parent();

  while (parent!=nullptr && parent->is_red()) {
    rb_node *grandparent = parent->get_parent();

    if (grandparent!=nullptr) {
      if (parent==grandparent->get_left()) {
        rb_node *uncle = grandparent->get_right();

        if (uncle!=nullptr && uncle->is_red()) {
          parent->set_red(false);
          uncle->set_red(false);
          grandparent->set_red(true);
          node = grandparent;
        } else {
          if (node==node->get_parent()->get_right()) {
            rotate_left(node);
            node = parent;
          }
          rotate_right(parent);
          parent->set_red(false);
          grandparent->set_red(true);
        }
      } else {
        rb_node *uncle = grandparent->get_left();

        if (uncle!=nullptr && uncle->is_red()) {
          parent->set_red(false);
          uncle->set_red(false);
          grandparent->set_red(true);
          node = grandparent;
        } else {
          if (node==node->get_parent()->get_left()) {
            rotate_right(node);
            node = parent;
          }
          rotate_left(parent);
          parent->set_red(false);
          grandparent->set_red(true);
        }
      }
    }
  }
  root->set_red(false);
}

void rb_tree::rotate_left(rb_node *node) {
  rb_node *parent = node->get_parent();
  if (parent==nullptr) {
    return;
  }
  rb_node *grandparent = parent->get_parent();
  if (grandparent!=nullptr) {
    node->set_parent(grandparent);
    if (grandparent->get_right()==parent) {
      grandparent->set_right(node);
    } else {
      grandparent->set_left(node);
    }
  } else {
    node->set_parent(nullptr);
    root = node;
  }
  if (node->get_left()!=nullptr) {
    node->get_left()->set_parent(parent);
  }
  parent->set_right(node->get_left());
  parent->set_parent(node);
  node->set_left(parent);
}

void rb_tree::rotate_right(rb_node *node) {
  rb_node *parent = node->get_parent();
  if (parent==nullptr) {
    return;
  }
  rb_node *grandparent = parent->get_parent();
  if (grandparent!=nullptr) {
    node->set_parent(grandparent);
    if (grandparent->get_right()==parent) {
      grandparent->set_right(node);
    } else {
      grandparent->set_left(node);
    }
  } else {
    node->set_parent(nullptr);
    root = node;
  }
  if (node->get_right()!=nullptr) {
    node->get_right()->set_parent(parent);
  }
  parent->set_left(node->get_right());
  parent->set_parent(node);
  node->set_right(parent);
}

// Getters and setters
rb_node *rb_tree::get_root() const {
  return root;
}

void rb_tree::set_root(rb_node *root) {
  rb_tree::root = root;
}