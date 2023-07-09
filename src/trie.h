#ifndef __TRIE_H__
#define __TRIE_H__

#include <codecvt>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <string>
#include <vector>

struct Word {
    std::wstring keyWord;
    std::wstring pronunciation;
    std::vector<std::wstring> definition;

    Word() = default;

    // Operator << to print Word
    friend std::wostream &operator<<(std::wostream &os, const Word &word) {
        os << word.keyWord << std::endl;
        os << word.pronunciation << std::endl;
        for (const auto &def : word.definition) {
            os << def << std::endl;
        }
        return os;
    }
};

class Trie {
public:
    Trie();

    void insert(const std::wstring &word);
    void insert(const Word &word);
    void insert(const std::vector<Word> &words);
    void insert(const std::wstring &word, const std::wstring &pronunciation, const std::vector<std::wstring> &definition);

    bool search(const std::wstring &word) const;
    bool search(const std::wstring &word, Word &result) const;

    void load(const std::string &fileName);
    void save(const std::string &fileName) const;

private:
    struct Node {
        Node *children[39];
        bool isEndOfWord; // Mark if this node is the end of a word (or the word is in the dictionary)
        Word word;

        Node();
    };

    Node *root;

    int getIndex(const wchar_t &character) const;

    void load(Node *node, std::wifstream &file);
    void save(Node *node, std::wofstream &file) const;
};

#endif // __TRIE_H__
