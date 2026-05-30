// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int freq;
    Node *right;
    Node *left;
    explicit Node(const T& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
  };
  Node *root;
  void insert(Node*& node, const T& key) {
    if (node == nullptr) {
      node = new Node(key);
    } else if (key == node->key) {
      node->freq++;
    } else if (key > node->key) {
      insert(node->right, key);
    } else {
      insert(node->left, key);
    }
  }
  bool search(Node* node, const T& key) const {
        if (!node) {
          return false;
        }
        if (key == node->key) {
          return true;
        } else if (key > node->key) {
          return search(node->right, key);
        } else {
          return search(node->left, key);
        }
  }
  int depth(Node *node) const {
    if (node == nullptr) return 0;
    int rightElementDepth = depth(node->right);
    int leftElementDepth = depth(node->left);
    return std::max(rightElementDepth, leftElementDepth) + 1;
  }
  void gathering(Node *node, std::vector<std::pair<T, int>> &vect) const {
    if (node == nullptr) return;
    gathering(node->left, vect);
    vect.emplace_back(node->key, node->freq);
    gathering(node->right, vect);
  }
  void clear (Node *node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }
 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }
  void insert(const T& key) { insert(root, key); }
  bool search(const T& key) const { return search(root, key); }
  int depth() const { return depth(root); }
  std::vector<std::pair<T, int>> collectNodes () const {
    std::vector<std::pair<T, int>> res;
    gathering(root, res);
    return res;
  }
};

#endif  // INCLUDE_BST_H_
