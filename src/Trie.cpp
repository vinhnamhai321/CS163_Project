#include "Trie.h"
#include "Dictionary.h"
#include "HashMap.h"
#include <unordered_set>

extern Trie ev, ee, ve;
extern Trie ev_addWord, ee_addWord, ve_addWord;
extern Trie ev_edited, ee_edited, ve_edited;
void Trie::buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef) {
    Node *cur = root;
    auto len = keyWord.length();
    for (int pos = 0; pos < len; ++pos) {
        wchar_t letter = keyWord[pos];
        int index = getIndex(letter);

        if (!(0 <= index && index < 106)) {
            std::wcout << "Error to build trie at keyWord: " << keyWord << "\n";
            return;
        }

        if (!cur->character[index])
            cur->character[index] = new Node;
        cur = cur->character[index];
    }

    if (cur) {
        cur->isWord = 1;
        cur->word = new WordDef(keyWord, wordDef);
    }
}

void Trie::loadDataSet(std::string path) {
    std::wifstream fin(path);
    if (!fin.is_open())
        std::cout << "Error to load file\n";
    fin.imbue(std::locale(std::locale(),
                          new std::codecvt_utf8<wchar_t>)); // set input for UTF8 character from file
    std::wstring get;                                       // get first key word
    getline(fin, get);
    while (!fin.eof()) {
        std::vector<std::wstring> wordDef;
        std::wstring keyWord = get.substr(1, get.length() - 1); // remove '@' character from key word
        getline(fin, get);
        for (; !fin.eof() && get[0] != '@'; getline(fin, get)) // set condition whenever meet new key word
        {
            if (get[0] == L'-')
                myMap.push(get, keyWord);
            wordDef.push_back(get); // push all definition of current key word
        }
        buildTrie(keyWord, wordDef); // create new key word in trie
    }
}

void Trie::deleteTrie(Node *&root) {
    if (!root)
        return;
    for (int i = 0; i < 106; ++i)
        deleteTrie(root->character[i]);
    delete root;
}

WordDef *Trie::getRandomWord() {
    // Random function
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    Node *curNode = root;
    std::vector<short> indices;
    while (true) {
        // Get available indices
        indices.clear();
        for (short i = 0; i < 106; ++i)
            if (curNode->character[i]) {
                // Perfer [a-z0-9] more than other characters
                if (i <= 36)
                    indices.push_back(i);
                else if ((rng() % 1337) >= 1000)
                    indices.push_back(i);
            }

        // If no available indices, this is end of word or random went to sparse tree
        if (indices.empty()) {
            // Push remaining subtree
            for (short i = 37; i < 106; ++i)
                if (curNode->character[i])
                    indices.push_back(i);
            // If still no available indices, this is end of word
            if (indices.empty())
                break;
        }

        // Randomly choose an index
        std::shuffle(indices.begin(), indices.end(), rng);
        int index = indices[rng() % indices.size()];
        curNode = curNode->character[index];

        // If current node is a word, randomly choose to return or not
        if (curNode->isWord) {
            if ((rng() % 1337) >= 1200) {
                return (curNode->word);
            }
        }
    }

    // If curNode is a word, return it
    return (curNode->word);
}

int getIndex(wchar_t letter) {
    if (letter >= L'a' && letter <= L'z')
        return letter - L'a';

    if (letter >= L'0' && letter <= L'9')
        return 26 + letter - L'0';

    switch (letter) {
    case L'-':
        return 36;
        break;
    case L'\'':
        return 37;
        break;
    case L' ':
        return 38;
        break;
    case L'á':
        return 39;
        break;
    case L'à':
        return 40;
        break;
    case L'ả':
        return 41;
        break;
    case L'ã':
        return 42;
        break;
    case L'ạ':
        return 43;
        break;
    case L'é':
        return 44;
        break;
    case L'è':
        return 45;
        break;
    case L'ẻ':
        return 46;
        break;
    case L'ẽ':
        return 47;
        break;
    case L'ẹ':
        return 48;
        break;
    case L'ó':
        return 49;
        break;
    case L'ò':
        return 50;
        break;
    case L'ỏ':
        return 51;
        break;
    case L'õ':
        return 52;
        break;
    case L'ọ':
        return 53;
        break;
    case L'ú':
        return 54;
        break;
    case L'ù':
        return 55;
        break;
    case L'ủ':
        return 56;
        break;
    case L'ũ':
        return 57;
        break;
    case L'ụ':
        return 58;
        break;
    case L'ý':
        return 59;
        break;
    case L'ỳ':
        return 60;
        break;
    case L'ỷ':
        return 61;
        break;
    case L'ỹ':
        return 62;
        break;
    case L'ỵ':
        return 63;
        break;
    case L'ă':
        return 64;
        break;
    case L'ắ':
        return 65;
        break;
    case L'ằ':
        return 66;
        break;
    case L'ẳ':
        return 67;
        break;
    case L'ẵ':
        return 68;
        break;
    case L'ặ':
        return 69;
        break;
    case L'â':
        return 70;
        break;
    case L'ấ':
        return 71;
        break;
    case L'ầ':
        return 72;
        break;
    case L'ẩ':
        return 73;
        break;
    case L'ẫ':
        return 74;
        break;
    case L'ậ':
        return 75;
        break;
    case L'đ':
        return 76;
        break;
    case L'ê':
        return 77;
        break;
    case L'ế':
        return 78;
        break;
    case L'ề':
        return 79;
        break;
    case L'ể':
        return 80;
        break;
    case L'ễ':
        return 81;
        break;
    case L'ệ':
        return 82;
        break;
    case L'í':
        return 83;
        break;
    case L'ì':
        return 84;
        break;
    case L'ỉ':
        return 85;
        break;
    case L'ĩ':
        return 86;
        break;
    case L'ị':
        return 87;
        break;
    case L'ô':
        return 88;
        break;
    case L'ố':
        return 89;
        break;
    case L'ồ':
        return 90;
        break;
    case L'ổ':
        return 91;
        break;
    case L'ỗ':
        return 92;
        break;
    case L'ộ':
        return 93;
        break;
    case L'ơ':
        return 94;
        break;
    case L'ớ':
        return 95;
        break;
    case L'ờ':
        return 96;
        break;
    case L'ở':
        return 97;
        break;
    case L'ỡ':
        return 98;
        break;
    case L'ợ':
        return 99;
        break;
    case L'ư':
        return 100;
        break;
    case L'ứ':
        return 101;
        break;
    case L'ừ':
        return 102;
        break;
    case L'ử':
        return 103;
        break;
    case L'ữ':
        return 104;
        break;
    case L'ự':
        return 105;
        break;
    }

    return -1;
}

/// @brief Return pointer of Trie
/// @param data - 0: EE, 1: EV, 2: VE
/// @param type - 0: Trie, 1: Trie addWord, 2: Trie edited
/// @return Pointer of Trie
Trie *getTree(int data, int type) {
    if (data == 1) {
        switch (type) {
        case 1:
            return &ee_addWord;
            break;
        case 2:
            return &ee_edited;
            break;
        default:
            return &ee;
        }
    }
    if (data == 2) {
        switch (type) {
        case 1:
            return &ev_addWord;
            break;
        case 2:
            return &ev_edited;
            break;
        default:
            return &ev;
        }
    }
    if (data == 3) {
        switch (type) {
        case 1:
            return &ve_addWord;
            break;
        case 2:
            return &ve_edited;
            break;
        default:
            return &ve;
        }
    }
    return nullptr;
}

WordDef *search(int data, std::wstring keyWord) {
    return searchKeyWord(*getTree(data), keyWord);
}

WordDef *searchKeyWord(Trie &tree, std::wstring keyWord) {
    Node *cur = tree.root;
    size_t len = keyWord.length();
    for (int i = 0; i < len; ++i) {
        wchar_t letter = keyWord[i];
        int index = getIndex(letter);

        // If index out of bound (or non-existing character) or cur is nullptr, return nullptr
        if (index <= -1 || index >= 106 || cur == nullptr)
            return nullptr;

        cur = cur->character[index];
    }

    return (cur->isWord ? cur->word : nullptr);
}

void deleteTree() {
    ee.deleteTrie(ee.root);
    ee_addWord.deleteTrie(ee_addWord.root);
    ee_edited.deleteTrie(ee_edited.root);
    ev.deleteTrie(ev.root);
    ev_addWord.deleteTrie(ev_addWord.root);
    ev_edited.deleteTrie(ev_edited.root);
    ve.deleteTrie(ve.root);
    ve_addWord.deleteTrie(ve_addWord.root);
    ve_edited.deleteTrie(ve_edited.root);
}
