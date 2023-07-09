#include "Trie.h"
#include "Dictionary.h"
#include <unordered_set>
void Trie::buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef)
{
	Trie* cur{};
	auto len = keyWord.length();
	for (int pos = 0; pos < len; ++pos)
	{
		wchar_t letter = keyWord[pos];
		int index = getIndex(letter);
		if (!character[index])
		character[index] = new Trie;
		cur = character[index];
	}
	if(cur)
	{
		cur->isWord = 1;
		cur->word.keyWord = keyWord;
		cur->word.definition = wordDef;
	}
}

void Trie::loadDataSet(std::string path)
{
	(void)_setmode(_fileno(stdout), _O_U8TEXT);		//set output for UTF8 character on console
	std::wifstream fin(EV);
	if (!fin.is_open())
		std::cout << "Error to load file\n";
	fin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));	//set input for UTF8 character from file
	std::wstring get;		//get first key word
	getline(fin, get);
	while (!fin.eof())
	{
		std::vector<std::wstring> wordDef;
		std::wstring keyWord = get.substr(1, get.length() - 1);	//remove '@' character from key word
		getline(fin, get);
		for (; !fin.eof() && get[0] != '@'; getline(fin, get))	//set condition whenever meet new key word
			wordDef.push_back(get);		//push all definition of current key word
		buildTrie(keyWord, wordDef);	//create new key word in trie
	}
}

int getIndex(wchar_t letter)
{
	if (letter < L'a' || letter > L'z')
	{
		if(letter > L'0' && letter < L'9')
		return 26 + letter - L'0';
		else
		{
			switch (letter)
			{
			case L'-':
				return 36;
				break;
			case L'\'':
				return 37;
				break;
			case L' ':
				return 38;
			}
		}
	}
	return letter - L'a';
}