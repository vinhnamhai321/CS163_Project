#include "Dictionary.h"

// Get user input
int getInput() {
    std::wstring input;
    std::getline(std::wcin, input);
    std::wcin.ignore();

    // Check input
    if (input.length() != 1 || !isdigit(input[0]))
        return -1;

    return input[0] - L'0';
}

Trie ev, ee, ve;
Trie ev_addWord, ee_addWord, ve_addWord;
Trie ev_edited, ee_edited, ve_edited;

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
    ee.loadDataSet(EE);
    // ev.loadDataSet(EV);
    // ve.loadDataSet(VE);
}

int Dictionary::print_SelectMenu() {
    std::wcout << "1. Eng-Eng\n";
    std::wcout << "2. Eng-Vie\n";
    std::wcout << "3. Vie-Eng\n";
    std::wcout << "4. Exit\n";
    std::wcout << "Select data-set: ";

    return getInput();
}

int Dictionary::print_MainMenu() {
    std::wcout << "1. Search for key word.\n";
    std::wcout << "2. Search for definition.\n";
    std::wcout << "3. Add new word.\n";
    std::wcout << "4. Get random word & definition.\n";
    std::wcout << "5. Play guess the keyword quiz.\n";
    std::wcout << "6. Play guess the definition quiz.\n";
    std::wcout << "0. Return back to previous menu.\n";
    std::wcout << "Enter your choice: ";

    return getInput();
}

bool Dictionary::print_addWord() {
    std::wcout << "Input keyword: ";
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

void Dictionary::print_randomWord() {
    Trie *tree = getTree(this->currentTree);
    if (tree == nullptr) {
        std::wcout << "Can not find any word in dictionary\n";
        return;
    }

    WordDef *word = tree->getRandomWord();
    std::wcout << *word << '\n';
}

void Dictionary::addWord(std::wstring keyWord, std::vector<std::wstring> wordDef) {
    // Process keyWord to be lowercase
    for (wchar_t &c : keyWord)
        c = towlower(c);

    Trie *tree = getTree(this->currentTree, 1);
    tree->buildTrie(keyWord, wordDef);

    // Save to file
    std::string TreeName = "";
    switch (this->currentTree) {
    case 1:
        TreeName = "EV";
        break;
    case 2:
        TreeName = "EE";
        break;
    case 3:
        TreeName = "VE";
        break;
    }

    // Write as append mode to "TreeName_addWord.txt"
    std::wofstream file("./data-set/" + TreeName + "_addWord.txt", std::ios::app);
    file << '@' << keyWord << '\n';
    for (const std::wstring &def : wordDef)
        file << def << '\n';
}

// Provide four random definition and guess correct keyword
void Dictionary::keywordQuiz() {
    Trie *tree = getTree(this->currentTree);
    if (tree == nullptr) {
        std::wcout << "Can not find any word in dictionary\n";
        return;
    }

    // Get four random word
    std::vector<WordDef> wordList;
    for (int i = 0; i < 4; ++i)
        wordList.push_back(*tree->getRandomWord());

    // Random function
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    // Randomly choose a word to be correct answer
    std::shuffle(wordList.begin(), wordList.end(), rng);
    int correctIndex = rng() % 4;

    // Print question
    std::wcout << "What is the meaning of this keyword \"" << wordList[correctIndex].keyWord << "\"?\n";

    // Print answer
    short defintionIndexList[4]{}; // Store index of definition
    for (int i = 0; i < 4; ++i) {
        // Find the defintion then print out
        for (auto &c : wordList[i].definition) {
            if (c[0] == '-') {
                std::wcout << i + 1 << ". " << c << '\n';
                break;
            }
            defintionIndexList[i]++;
        }
    }

    // Get user input
    int input = -1;
    while (true) {
        std::wcout << "Your answer: ";
        input = getInput();

        // Check input
        if (input == -1 || input < 1 || input > 4)
            std::wcout << "Invalid input!\n";
        else
            break;
    }

    // Check answer
    if (input == correctIndex + 1)
        std::wcout << "Correct answer!\n";
    else {
        std::wcout << "Wrong answer!\n";
        std::wcout << "Correct answer is: " << wordList[correctIndex].definition[defintionIndexList[correctIndex]] << '\n';
    }
}

void Dictionary::process() {
    while (true) {
        currentTree = print_SelectMenu();

        if (currentTree == -1 || currentTree == 4)
            break;

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
                print_randomWord();
                break;

            case 5:
                keywordQuiz();
                break;

            default:
                back = 1;
                break;
            }
        }
    }

    deleteTree();
    return;
}
