#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <io.h>
#include <fcntl.h>
struct Word
{
	std::wstring keyWord;
	std::vector<std::wstring> definition;
};
class Trie
{
public:
	void buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef);
	void loadDataSet(std::string path);		//load EV and EE file
private:
	Trie* character[38]{};
	bool isWord{};
	Word word;
};

int getIndex(wchar_t letter);				//return index for trie