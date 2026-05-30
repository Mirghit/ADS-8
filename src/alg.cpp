// Copyright 2021 NNTU-CS
#include "bst.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

void makeTree(BST<std::string>& tree, const char *filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }
    std::string word;
    char ch;
    while (file.get(ch)) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch - 'A' + 'a';
            }
            word.push_back(ch);
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
    auto nodes = tree.collectNodes();   // добавлено
    std::sort(nodes.begin(), nodes.end(),
        [](const std::pair<std::string, int>& a,
           const std::pair<std::string, int>& b) {
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
