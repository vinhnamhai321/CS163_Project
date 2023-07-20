#include "Trie.h"
#include "Dictionary.h"
#include <unordered_set>
void Trie::buildTrie(std::wstring keyWord, std::vector<std::wstring> wordDef)
{
	Node* cur = root;
	auto len = keyWord.length();
	for (int pos = 0; pos < len; ++pos)
	{
		wchar_t letter = keyWord[pos];
		int index = getIndex(letter);
		if (!cur->character[index])
			cur->character[index] = new Node;
		cur = cur->character[index];
	}
	if(cur)
	{
		cur->isWord = 1;
		cur->word = new WordDef(keyWord, wordDef);
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

void Trie::deleteTrie(Node*& root)
{
	if (!root)
		delete root;
	else
	{
		for (int i = 0; i < 38; ++i)
			deleteTrie(root->character[i]);
		delete root;
	}
}




WordDef* search(Trie tree, std::wstring keyWord)
{
	Node* cur = tree.root;
	int len = keyWord.length();
	for (int i = 0; i < len; ++i)
	{
		wchar_t letter = keyWord[i];
		int index = getIndex(letter);
		cur = cur->character[index];
		if (!cur)
			return nullptr;
	}
	if (!cur->isWord)
		return nullptr;
	return cur->word;
}