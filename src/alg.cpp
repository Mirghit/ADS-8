// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include  <algorithm>
#include  <string>
#include  <cctype>

void makeTree(BST<std::string>& tree, const char *filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Не удалось открыть файл: " << filename << std::endl;
    return;
  }
  std::string word;
  char currSymbol;
  while (file.get(currSymbol)) {
    if ((currSymbol >= 'A' && currSymbol <= 'Z') 
      || (currSymbol >= 'a' && currSymbol <= 'z')) {
      if (currSymbol >= 'A' && currSymbol <= 'Z') {
        currSymbol = currSymbol - 'A' + 'a';
      }
      word.push_back(currSymbol);
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
  auto nodes = tree.collectNodes();
  std::sort(nodes.begin(), nodes.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
  std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Не удалось открыть result/freq.txt" << std::endl;
    }

    for (const auto& p : nodes) {
        std::cout << p.first << " - " << p.second << std::endl;
        if (outFile) {
            outFile << p.first << " - " << p.second << std::endl;
        }
    }
    outFile.close();
}
