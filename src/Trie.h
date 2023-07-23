#pragma once

#include <fstream>
#include <iostream>

#include <string>
#include <vector>

#include <codecvt>
#include <fcntl.h>
#include <io.h>

#include "HashMap.h"
struct WordDef {
    // Constructor
    WordDef(std::wstring KeyWord, std::vector<std::wstring> WordDef) : keyWord(KeyWord), definition(WordDef) {
    }

    // Function
    std::wstring keyWord;
    std::vector<std::wstring> definition;

    // Ostream <<
    friend std::wostream &operator<<(std::wostream &os, const WordDef &word) {
        os << "Word: " << word.keyWord << std::endl;
        for (std::wstring item : word.definition)
            os << item << std::endl;
        return os;
    }
};

struct Node {
    Node *character[106]{};
    bool isWord{};
    WordDef *word{};
};

class Trie {
public:
    Node *root = new Node;

    // Tree Main Function
    void deleteTrie(Node *&root);
    void buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef);
    void loadDataSet(std::string path); // load EV and EE file

    // Tree Support Function
    WordDef *getRandomWord();

    // Map
    HashMap myMap;
};

int getIndex(wchar_t letter); // return index for trie

WordDef *searchKeyWord(Trie &tree, std::wstring keyWord);

WordDef *search(int data, std::wstring keyWord);

Trie *getTree(int data);

void deleteTree();
