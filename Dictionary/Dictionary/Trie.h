#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <utility>
#include <iostream>
struct Word
{
	std::wstring keyWord;
	std::vector<std::wstring> definition;
};
struct Node
{
	Node* character[39]{};
	bool isWord{};
	Word word;
};
class Trie
{
public:
	void deleteTrie(Node*& root);
	void buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef);
	void loadDataSet(std::string path);		//load EV and EE file
	std::pair<Word,bool> search(std::wstring keyWord);
	Node* root = new Node;
};

int getIndex(wchar_t letter);				//return index for trie