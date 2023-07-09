#include "src/trie.h"
#include <stdio.h>
#include <windows.h>

#define EV_Path "Data-set/EV_final.txt"

int main(int argc, char *argv[]) {
    // Set console to output UTF8
    std::ios_base::sync_with_stdio(false);
    SetConsoleOutputCP(CP_UTF8);

    Trie trie;

    trie.load(EV_Path);

    std::wcout << trie.search(L"abandon") << std::endl;

    Word result;
    trie.search(L"abandon", result);

    std::wcout << result << std::endl;

    return 0;
}
