// Copyright 2021 NNTU-CS
#include "bst.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void makeTree(BST<std::string>& tree, const char *filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Не удалось открыть файл: " << filename << std::endl;
    return;
  }
  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
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
    std::vector<std::pair<std::string, int>> fileWords = tree.collectNodes();
    std::sort(fileWords.begin(), fileWords.end(),
      [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    std::ofstream outFile("result/freq.txt");
    for (const auto& p : fileWords) {
      std::cout << p.first << " - " << p.second << std::endl;
      outFile << p.first << " - " << p.second << std::endl;
    }
    outFile.close();
}
