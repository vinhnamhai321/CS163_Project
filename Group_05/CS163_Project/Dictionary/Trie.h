#pragma once
#include <vector>
#include <fstream>
#include"HashMap.h"
struct WordDef
{
	//constructor
	WordDef(std::wstring KeyWord, std::vector<std::wstring> WordDef) :keyWord(KeyWord), definition(WordDef) {}
	//function
	std::wstring keyWord;
	std::vector<std::wstring> definition;
};

struct Node
{
	Node* character[200]{};
	bool isWord{};
	WordDef* word{};
	bool isEdit{};
	WordDef* editedWord{};
};

class Trie
{
public:

	//function
	void buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef);
	void editWord(std::wstring keyWord, std::vector<std::wstring> wordDef);
	void loadDataSet(std::string path, std::vector<WordDef> &word, HashMap& myMap, bool isEdit = 0);
	Node* root = new Node;
	
};

int getIndex(wchar_t letter);				

WordDef* search(Trie tree, std::wstring keyWord);


