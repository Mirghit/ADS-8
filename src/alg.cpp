// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>

void makeTree(BST<std::string>& tree, const char *filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "Не удалось открыть файл: " << filename << std::endl;
    return;
  }
  std::string word;
  char currSymbol;
  while (file.get(currSymbol)) {
    unsigned char unsChr = static_cast<unsigned char>(currSymbol);
    if (std::isalpha(unsChr)) {
      word.push_back(std::tolower(unsChr));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::sort(nodes.begin(), nodes.end(),
    [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      if (a.second != b.second) return a.second > b.second;
      return a.first < b.first;
    });
  std::ofstream outFile("result/freq.txt");
  for (const auto& p : nodes) {
    std::cout << p.first << " - " << p.second << std::endl;
    if (outFile) {
      outFile << p.first << " - " << p.second << std::endl;
    }
  }
  outFile.close();
}
