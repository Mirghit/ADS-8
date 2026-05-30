// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>
#include <utility>
#include <string>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int freq;
    Node *left;
    Node *right;
    explicit Node(const T& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
  };

  Node *root;
  int len;

  void insert(Node*& node, const T& k) {
    if (node == nullptr) {
      node = new Node(k);
      len++;
      return;
    }
    if (k == node->key) {
      node->freq++;
    } else if (k > node->key) {
      insert(node->right, k);
    } else {
      insert(node->left, k);
    }
  }

  bool search(Node* node, const T& k) const {
    if (node == nullptr) return 0;
    if (k == node->key) return node->freq;
    if (k > node->key) return search(node->right, k);
    return search(node->left, k);
  }

  int depth(Node *node) const {
    if (node == nullptr) return 0;
    return 1 + std::max(depth(node->left), depth(node->right));
  }

  void gathering(Node *node, std::vector<std::pair<T, int>>& vect) const {
    if (node == nullptr) return;
    gathering(node->left, vect);
    vect.push_back(std::make_pair(node->key, node->freq));
    gathering(node->right, vect);
  }

  void clear(Node *node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr), len(0) {}
  ~BST() { clear(root); }

  void insert(const T& k) { insert(root, k); }
  bool search(const T& k) const { return search(root, k); }
  int depth() const { return depth(root); }
  int size() const { return len; }
  bool empty() const { return root == nullptr; }

  std::vector<std::pair<T, int>> collectNodes() const {
    std::vector<std::pair<T, int>> res;
    gathering(root, res);
    return res;
  }
};

#endif  // INCLUDE_BST_H_
