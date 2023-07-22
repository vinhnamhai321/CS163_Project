#include "Dictionary.h"
#include "Trie.h"

Trie ev, ee, ve;
void Dictionary::run() {
    build();
    process();
}

void Dictionary::build() {
    // Initialize UTF-8 for input and output
    (void)_setmode(_fileno(stdin), _O_U16TEXT);
    (void)_setmode(_fileno(stdout), _O_U8TEXT);
    std::ios_base::sync_with_stdio(true);

    // Load dataset
    //ee.loadDataSet(EE);
    //ev.loadDataSet(EV);
    ve.loadDataSet(VE);

    // Clear tree
    // deleteTree();
}

int Dictionary::print_SelectMenu() {
    std::wcout << "1. Eng-Eng\n";
    std::wcout << "2. Eng-Vie\n";
    std::wcout << "3. Vie-Eng\n";
    std::wcout << "4. Exit\n";
    std::wcout << "Select data-set: ";

    std::wstring input;
    std::getline(std::wcin, input);
    std::wcin.ignore();

    // Check input
    if (input.length() != 1)
        return -1;
    if (input[0] < L'1' || input[0] > L'4')
        return -1;

    return input[0] - L'0';
}

int Dictionary::print_MainMenu() {
    std::wcout << "1. Search for key word.\n";
    std::wcout << "2. Search for definition.\n";
    std::wcout << "3. Add new word.\n";
    std::wcout << "4. Get random word & definition.\n";
    std::wcout << "0. Return back to previous menu.\n";
    std::wcout << "Enter your choice: ";

    std::wstring input;
    std::getline(std::wcin, input);
    std::wcin.ignore();

    // Check input
    if (input.length() != 1)
        return -1;
    if (input[0] < L'1' || input[0] > L'5')
        return -1;

    return input[0] - L'0';
}

bool Dictionary::print_addWord() {
    std::wcout << "Input word: ";
    std::wstring keyWord;
    std::getline(std::wcin, keyWord);
    std::wcin.ignore();

    std::vector<std::wstring> wordDef;

    std::wcout << "Input definition (Enter \"*\" to end): ";
    std::wstring definition;

    while (true) {
        std::getline(std::wcin, definition);
        std::wcin.ignore();

        if (definition == L"*")
            break;

        wordDef.push_back(definition);
    }

    addWord(keyWord, wordDef);
    return 1;
}

void Dictionary::addWord(std::wstring keyWord, std::vector<std::wstring> wordDef) {
    // Process keyWord to be lowercase
    for (wchar_t &c : keyWord)
        c = towlower(c);

    Trie *tree = getTree(this->currentTree);
    if (tree == nullptr)
        return;
    tree->buildTrie(keyWord, wordDef);
}

// Random function
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void Dictionary::getRandomWord() {
    Trie *tree = getTree(this->currentTree);
    if (tree == nullptr)
        return;

    Node *curNode = tree->root;
    std::vector<short> indices;
    while (true) {
        // Get available indices
        indices.clear();
        for (short i = 0; i < 106; ++i)
            if (curNode->character[i])
                indices.push_back(i);

        // If no available indices, break
        if (indices.empty())
            break;

        // Randomly choose an index
        int index = indices[rng() % indices.size()];
        curNode = curNode->character[index];

        // If current node is a word, randomly choose to print or not
        if (curNode->isWord) {
            if ((rng() % 1337) >= 668) {
                std::wcout << *(curNode->word) << '\n';
                return;
            }
        }
    }

    // If curNode is a word, print it
    if (curNode->isWord)
        std::wcout << *(curNode->word) << '\n';
}

void Dictionary::process() {
    while (true) {
        currentTree = print_SelectMenu();

        if (currentTree == -1 || currentTree == 4) {
            deleteTree();
            break;
        }

        bool back = 0;
        while (!back) {
            int choice = print_MainMenu();

            switch (choice) {
            case 1: {
                std::wstring inputString;
                std::wcout << "Input: ";

                std::getline(std::wcin, inputString);
                std::wcin.ignore();
                WordDef *find = search(currentTree, inputString);

                if (!find)
                    std::wcout << "Can not find this word in dictionary\n";
                else {
                    std::wcout << *find << '\n';
                }
                break;
            }
            /*case 2:
			{
				std::wstring inputString;
				getline(std::wcin, inputString);
				WordDef* find = searchDefinition(, inputString);
				if (!find)
					std::wcout << "Can not find this word in dictionary\n";
				else
				{
					std::wcout << "Word: " << find->keyWord << std::endl;
					for (std::wstring item : find->definition)
						std::wcout << item << std::endl;
				}
				break;
			}*/
            case 3:
                print_addWord();
                break;

            case 4:
                getRandomWord();
                break;

            default:
                back = 1;
                break;
            }
        }
    }
}
