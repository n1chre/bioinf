//
// Created by Matija Orsolic on 28/12/2016.
//

#include "rb_tree.h"

// Constructor
rb_tree::rb_tree(std::vector<data *> &nodes) {
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

const uint32_t rb_tree::rank(char i, uint32_t idx) const {
  return 0;
}

const uint32_t rb_tree::select(char i, uint32_t idx) const {
  return 0;
}

// Private functions
rb_node *rb_tree::insert_recursive(data *d, rb_node *node, rb_node *new_node) {
  if (node==nullptr) {
    node = new_node;
  } else if (d->get_starting_idx() > node->get_d()->get_starting_idx()) {
    node->set_right(insert_recursive(d, node->get_right(), new_node));
  } else {
    node->set_left(insert_recursive(d, node->get_left(), new_node));
  }
  return node;
}

void rb_tree::insert_fixup(rb_node *node) {
  while (node->get_parent()->is_red()) {
    rb_node *parent = node->get_parent();
    rb_node *grandparent = parent->get_parent();

    if (parent == grandparent->get_left()) {
      rb_node *uncle = grandparent->get_right();

      if (uncle->is_red()) {
        parent->set_red(false);
        uncle->set_red(false);
        grandparent->set_red(true);
        node = grandparent;
      } else {
        if (node == node->get_parent()->get_right()) {
          rotate_left(node);
          node = parent;
        }
        rotate_right(parent);
        parent->set_red(false);
        grandparent->set_red(true);
      }
    } else {
      rb_node *uncle = grandparent->get_left();

      if (uncle->is_red()) {
        parent->set_red(false);
        uncle->set_red(false);
        grandparent->set_red(true);
        node = grandparent;
      } else {
        if (node == node->get_parent()->get_left()) {
          rotate_right(node);
          node = parent;
        }
        rotate_left(parent);
        parent->set_red(false);
        grandparent->set_red(true);
      }
    }
  }

  root->set_red(false);
}

rb_node *rb_tree::rotate_left(rb_node *node) {
  rb_node *parent = node->get_parent();
  if (parent == NULL) {
    return NULL;
  }

  rb_node *grandparent = node->get_parent()->get_parent();
  if (grandparent != NULL) {
    if (grandparent->get_right() == parent) {
      grandparent->set_right(node);
    } else {
      grandparent->set_left(node);
    }
  }

  parent->set_right(node->get_left());
  node->set_left(parent);

  return NULL;
}

rb_node *rb_tree::rotate_right(rb_node *node) {
  rb_node *parent = node->get_parent();
  if (parent == NULL) {
    return NULL;
  }

  rb_node *grandparent = node->get_parent()->get_parent();
  if (grandparent != NULL) {
    if (grandparent->get_right() == parent) {
      grandparent->set_right(node);
    } else {
      grandparent->set_left(node);
    }
  }

  parent->set_left(node->get_right());
  node->set_right(parent);

  return NULL;
}

// Getters and setters
rb_node *rb_tree::get_root() const {
  return root;
}

void rb_tree::set_root(rb_node *root) {
  rb_tree::root = root;
}
