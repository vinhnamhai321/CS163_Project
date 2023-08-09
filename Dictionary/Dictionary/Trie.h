#pragma once

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <codecvt>
#include <io.h>
#include <fcntl.h>

#include "HashMap.h"
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
	Node* character[155]{};
	bool isWord{};
	WordDef* word{};
};

class Trie
{
public:

	//function
	void deleteTrie(Node*& root);
	void buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef);
	void loadDataSet(std::string path);		//load EV and EE file
	Node* root = new Node;

	//Map
	HashMap myMap;
};

int getIndex(wchar_t letter);				//return index for trie

WordDef* searchKeyWord(Trie& tree, std::wstring keyWord);

WordDef* search(int data, bool option, std::wstring keyWord);

std::vector<std::wstring> suggestWord(int data, std::wstring input);	//get the input data for specific data-set

void crawl(std::wofstream& fout, Node*& cur);

std::vector<std::wstring> crawl(Trie& tree, std::wstring input);	/*return vector include suggested words
																	for input string*/
void crawl(Node*& cur, std::vector<std::wstring> word);				//crawl from the start point - find suggested word

WordDef* searchDefinition(Trie& tree, std::wstring def);

void clearDataset();

void deleteTree();

void deleteMap();