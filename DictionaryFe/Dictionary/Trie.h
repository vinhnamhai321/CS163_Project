#pragma once
#include <vector>
#include <fstream>

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
};

class Trie
{
public:

	//function
	void buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef);
	void loadDataSet(std::string path, std::vector<WordDef> &word);		
	Node* root = new Node;
};

int getIndex(wchar_t letter);				

WordDef* search(Trie tree, std::wstring keyWord);

