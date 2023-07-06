#pragma once
#include <string>
#include <vector>
struct Word
{
	std::string keyWord, pronunciation;
	std::vector<std::string> definition;
};
struct Trie
{
	Trie* character[26]{};
	bool isWord;
	Word word;
};


