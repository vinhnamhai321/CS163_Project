#pragma once
#include "Trie.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

class Dictionary {
    int currentTree;

public:
    void run();
    void build();
    void process();

private:
    int print_SelectMenu();
    int print_MainMenu();
    bool print_addWord();
    void print_randomWord();

    void addWord(std::wstring keyWord, std::vector<std::wstring> wordDef);
    void meaningQuiz();
    void keywordQuiz();
};

// Path of data-set
#define EV "./Data-set/EV_final.txt"
#define EE "./Data-set/EE_final.txt"
#define VE "./Data-set/VE_final.txt"

// Function load data-set
