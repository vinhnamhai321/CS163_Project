#include "trie.h"

/*
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
        bool isEndOfWord;
        Word word;

        Node();
    };

    Node *root;

    int getIndex(const wchar_t &character) const;

    void load(Node *node, std::wifstream &file);
    void save(Node *node, std::wofstream &file) const;
};
*/

/// Trie begin
// Public function

Trie::Trie() {
    root = new Node();
}

void Trie::insert(const std::wstring &word) {
    insert(word, L"", std::vector<std::wstring>());
}

void Trie::insert(const Word &word) {
    insert(word.keyWord, word.pronunciation, word.definition);
}

void Trie::insert(const std::vector<Word> &words) {
    for (const auto &word : words) {
        insert(word);
    }
}

void Trie::insert(const std::wstring &word, const std::wstring &pronunciation, const std::vector<std::wstring> &definition) {
    Node *node = root;

    for (auto &c : word) {
        int index = getIndex(c);
        if (index == -1) {
            std::wcerr << L"Error: Invalid character " << c << std::endl;
            return;
        }

        if (node->children[index] == nullptr) {
            node->children[index] = new Node();
        }
        node = node->children[index];
    }

    // Assign word to node
    node->isEndOfWord = true;
    node->word.keyWord = word;
    node->word.pronunciation = pronunciation;
    node->word.definition = definition;
}

bool Trie::search(const std::wstring &word) const {
    Word result;
    return search(word, result);
}

bool Trie::search(const std::wstring &word, Word &result) const {
    int index = 0;
    Node *node = root;

    for (auto &c : word) {
        index = getIndex(c);
        if (index == -1) {
            std::wcerr << L"Error: Invalid character " << c << std::endl;
            return false;
        }

        if (node->children[index] == nullptr) {
            return false;
        }
        node = node->children[index];
    }

    if (node->isEndOfWord) {
        result = node->word;
        return true;
    }

    return false;
}

void Trie::load(const std::string &fileName) {
    std::wifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    load(root, file);
    file.close();
}

void Trie::save(const std::string &fileName) const {
    std::wofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    save(root, file);
    file.close();
}

// Private function

Trie::Node::Node() {
    for (int i = 0; i < 39; ++i) {
        children[i] = nullptr;
    }
    isEndOfWord = false;
}

int Trie::getIndex(const wchar_t &character) const {
    // Alphabet
    if (character >= L'a' && character <= L'z')
        return character - L'a';
    if (character >= L'A' && character <= L'Z')
        return character - L'A';

    // Number
    if (character >= L'0' && character <= L'9')
        return character - L'0' + 26;

    // Special character
    if (character == L'\'')
        return 36;
    if (character == L'-')
        return 37;
    if (character == L' ')
        return 38;

    return -1;
}

void Trie::load(Node *node, std::wifstream &file) {
    std::wstring line = L"";
    std::wstring keyWord = L"";
    std::wstring pronunciation = L"";
    std::vector<std::wstring> definition;

    // Get first keyword
    std::getline(file, line);

    while (file.eof() == false) {
        // Remove the first '@' character
        if (line[0] == L'@')
            line.erase(0, 1);

        // Assign key word from last line
        keyWord = line;

        // Get pronunciation
        std::getline(file, pronunciation);

        // Get definition
        definition.clear();
        while (std::getline(file, line) && line[0] != L'@')
            definition.push_back(line);

        // Push to trie
        insert(keyWord, pronunciation, definition);
    }
}

void Trie::save(Node *node, std::wofstream &file) const {
    if (node->isEndOfWord) {
        file << '@' << node->word.keyWord << std::endl;
        file << node->word.pronunciation << std::endl;
        for (const auto &line : node->word.definition) {
            file << line << std::endl;
        }
    }

    for (int i = 0; i < 39; ++i) {
        if (node->children[i] != nullptr) {
            save(node->children[i], file);
        }
    }
}

/// Trie end
