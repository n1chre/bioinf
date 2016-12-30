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
  insert_recursive(root, node);
  insert_fixup(node);
}

// Private functions
void rb_tree::insert_recursive(rb_node *root, rb_node *node) {
  if (root == NULL) {
    root = node;
    return;
  }

  /*if (root->get_block_number() > node->get_block_number()) {
    insert_recursive(root->get_right(), node);
  } else {
    insert_recursive(root->get_left(), node);
  }*/
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
