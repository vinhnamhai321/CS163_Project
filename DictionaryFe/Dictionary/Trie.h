#pragma once
#include <vector>
#include <fstream>
#include"HashMap.h"
#include"system.h"
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

	////Map
	//HashMap myMap;
};

int getIndex(wchar_t letter);				

WordDef* search(Trie tree, std::wstring keyWord);

//std::vector<std::wstring> suggestWord(data* _data, std::wstring dtset, std::wstring input);	//get the input data for specific data-set
//
//void crawl(std::wofstream& fout, Node*& cur);
//
//std::vector<std::wstring> crawl(Trie& tree, std::wstring input);	/*return vector include suggested words
//																	for input string*/
//void crawl(Node*& cur, std::vector<std::wstring>& word);				//crawl from the start point - find suggested word
//WordDef* searchDefinition(Trie& tree, std::wstring def);
