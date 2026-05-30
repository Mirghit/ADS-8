// Copyright 2021 NNTU-CS

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int freq;
    Node* left;
    Node* right;
    explicit Node(const T& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
  };
  Node* root;
  int len;

  void add(Node*& node, const T& k) {
    if (node == nullptr) {
      node = new Node(k);
      len++;
      return;
    }
    if (k < node->key) {
      add(node->left, k);
    } else if (k > node->key) {
      add(node->right, k);
    } else {
      node->freq++;
    }
  }

  int founder(Node* node, const T& k) const {
    if (node == nullptr) return 0;
    if (k == node->key) return node->freq;
    if (k < node->key) return founder(node->left, k);
    return founder(node->right, k);
  }

  int depthOfTree(Node* node) const {
    if (node == nullptr) return -1;
    int leftH = depthOfTree(node->left);
    int rightH = depthOfTree(node->right);
    return std::max(leftH, rightH) + 1;
  }

  void gathering(Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (node == nullptr) return;
    gathering(node->left, vec);
    vec.push_back(std::make_pair(node->key, node->freq));
    gathering(node->right, vec);
  }

  void clear(Node* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr), len(0) {}
  ~BST() { clear(root); }

  bool empty() const { return root == nullptr; }
  void insert(const T& k) { add(root, k); }
  int depth() const { return depthOfTree(root); }
  int search(const T& k) const { return founder(root, k); }
  int size() const { return len; }
  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> res;
    gathering(root, res);
    return res;
  }
};

#endif  // INCLUDE_BST_H_
