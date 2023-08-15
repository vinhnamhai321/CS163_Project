#include"HandmadeFunc.h"
#include<fstream>
#include<vector>
#include<locale>
#include<codecvt>
#include<iostream>
#include<ctime>
sf::RectangleShape createRectangleShape(float width, float height, float x, float y)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	return shape;

}
sf::Text createText(std::wstring string, float x, float y, int size)
{
	sf::Text text;
	text.setString(string);
	text.setPosition(sf::Vector2f(x, y));
	text.setCharacterSize(size);
	return text;
}
void removeWord(std::wstring line, std::wstring path)
{
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::wfstream fin(path, std::ios::in);
	fin.imbue(loc);
	std::wstring get;
	std::vector<std::wstring> save;
	while (!fin.eof())
	{
		getline(fin, get);
		if(get.empty())
			continue;
		save.push_back(get);
	}
	fin.close();
	std::wfstream fout(path, std::ios::out);
	fout.imbue(loc);
	for (int i = 0; i < save.size(); i++)
	{
		if (save[i] == line)
			continue;
		fout << save[i] << std::endl;
	}
	fout.close();
}
Trie getDataset(std::wstring dataset, data* _data)
{
	if (dataset == L"Eng-Eng")
	{
		return _data->ee;
	}
	else if (dataset == L"Eng-Vi")
	{
		return _data->ev;
	}
	else if (dataset == L"Vi-Eng")
	{
		return _data->ve;
	}
	else if (dataset == L"Emoji")
	{
		return _data->emoji;
	}
}
bool existWord(std::wstring line, std::wstring path)
{
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::wfstream fin(path, std::ios::in);
	fin.imbue(loc);
	std::wstring get;
	while (!fin.eof())
	{
		getline(fin, get);
		if (get == line)
		{
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}
std::wstring randomWord(data* _data, int id)
{
	srand(time(NULL));
	if (id == -1)
	{
		id = rand() % 3;
	}
	std::wstring data;
	std::wstring word;
	std::wstring line;
	if (id == 0)
	{
		data = L"Eng-Eng";
		int idx = rand() % _data->eeKeyword.size();
		word = _data->eeKeyword[idx].keyWord;
		while (existWord(word + L"(" + data + L")", L"Resource\\RemoveWord.txt"))
		{
			idx = rand() % _data->eeKeyword.size();
			word = _data->eeKeyword[idx].keyWord;
		}
		line = word + L"(" + data + L")";
	}
	if (id == 1)
	{
		data = L"Eng-Vi";
		int idx = rand() % _data->evKeyword.size();
		word = _data->evKeyword[idx].keyWord;
		while (existWord(word + L"(" + data + L")", L"Resource\\RemoveWord.txt"))
		{
			idx = rand() % _data->eeKeyword.size();
			word = _data->evKeyword[idx].keyWord;
		}
		line = word + L"(" + data + L")";
	}
	if (id == 2)
	{
		data = L"Vi-Eng";
		int idx = rand() % _data->veKeyword.size();
		word = _data->veKeyword[idx].keyWord;
		while (existWord(word + L"(" + data + L")", L"Resource\\RemoveWord.txt"))
		{
			idx = rand() % _data->eeKeyword.size();
			word = _data->veKeyword[idx].keyWord;
		}
		line = word + L"(" + data + L")";
	}
	return line;
}
void addWord(std::wstring keyWord, std::vector<std::wstring> wordDef, std::wstring dataset, data* _data) {
	// Process keyWord to be lowercase
	for (wchar_t& c : keyWord)
		c = towlower(c);

	Trie tree = getDataset(dataset, _data);
	tree.buildTrie(keyWord, wordDef);

	// Save to file
	std::wofstream file(L"Resource\\" + dataset + L"addWord.txt", std::ios::app);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	file.imbue(loc);
	file << '@' << keyWord << '\n';
	for (const std::wstring& def : wordDef)
		file << def << '\n';
}

void editWord(std::wstring keyWord, std::vector<std::wstring> wordDef, std::wstring dataset, data* _data) {
	// Process keyWord to be lowercase
	for (wchar_t& c : keyWord)
		c = towlower(c);

	Trie tree = getDataset(dataset, _data);
	tree.editWord(keyWord, wordDef);

	// Save to file
	std::wofstream file(L"Resource\\" + dataset + L"editWord.txt", std::ios::app);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	file.imbue(loc);
	file << '@' << keyWord << '\n';
	for (const std::wstring& def : wordDef)
		file << def << '\n';
}
void crawl(std::wofstream& fout, Node*& cur)
{
	if (!cur)
		return;
	if (cur->isWord)
	{
		std::wstring s;
		for (std::wstring item : cur->word->definition)
			s += item;
		fout << L"@" << cur->word->keyWord << s << std::endl;
	}
	for (int i = 0; i < 106; ++i)
		crawl(fout, cur->character[i]);
}
std::vector<std::wstring> suggestWord(data* _data, std::wstring dtset, std::wstring input)
{
	if (dtset == L"Eng-Eng")
	{
		return crawl(_data->ee, input);
	}
	if (dtset == L"Eng-Vi")
	{
		return crawl(_data->ev, input);
	}
	if (dtset == L"Vi-Eng")
	{
		return crawl(_data->ve, input);
	}
	if (dtset == L"Emoji")
	{
		return crawl(_data->emoji, input);
	}
}

std::vector<std::wstring> crawl(Trie& tree, std::wstring input)
{
	std::vector<std::wstring> suggestWord;
	Node* cur = tree.root;
	size_t len = input.length();
	for (int i = 0; i < len; ++i)
	{
		wchar_t letter = input[i];
		int index = getIndex(letter);
		cur = cur->character[index];
		if (!cur)
			return suggestWord;
	}
	for (int i = 0; i < 155; ++i)
	{
		crawl(cur->character[i], suggestWord);
	}

	return suggestWord;
}

void crawl(Node*& cur, std::vector<std::wstring>& word)
{
	if (!cur)
		return;
	if (cur->isWord)
	{
		std::wstring s;
		word.push_back(cur->word->keyWord);
	}
	for (int i = 0; i < 106; ++i)
		crawl(cur->character[i], word);
}

HashMap &getMap(std::wstring dataset, data* _data)
{
	if (dataset == L"Eng-Eng")
	{
		return _data->eeMap;
	}
	else if (dataset == L"Eng-Vi")
	{
		return _data->evMap;
	}
	else if (dataset == L"Vi-Eng")
	{
		return _data->veMap;
	}
	else if (dataset == L"Emoji")
	{
		return _data->emojiMap;
	}
}

std::wstring searchDefinition(Trie tree, std::wstring def, HashMap& myMap)
{
	long long idx = setIndex(def);
	std::wstring findKey{};
	for (Table* cur = myMap.myTable[idx]; cur; cur = cur->pNext)
	{
		if (def.compare(cur->def) == 0)
			findKey = cur->keyWord;
	}
	return findKey;
}

void remove(Trie& tree, std::wstring keyword)
{
	Node* cur = tree.root;
	size_t len = keyword.length();
	for (int i = 0; i < len; i++)
	{
		wchar_t letter = keyword[i];
		int index = getIndex(letter);
		cur = cur->character[index];
		if (!cur && cur->word->keyWord == keyword) {
			break;
		}
	}
	if (!cur) return;
	cur->isWord = 0;
	delete cur->word;
}
void resetAddWord(Trie tree, std::wstring path)
{
	std::wifstream fin(path);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	fin.imbue(loc);
	std::wstring get;		
	getline(fin, get);
	while (!fin.eof())
	{
		std::vector<std::wstring> wordDef;
		std::wstring keyWord = get.substr(1, get.length() - 1);	//remove '@' character from key word
		remove(tree, keyWord);
		getline(fin, get);
		for (; !fin.eof() && get[0] != '@'; getline(fin, get))	
		{

		}
	}
	fin.close();
}

void removeEditWord(Trie& tree, std::wstring keyword)
{
	Node* cur = tree.root;
	size_t len = keyword.length();
	for (int i = 0; i < len; i++)
	{
		wchar_t letter = keyword[i];
		int index = getIndex(letter);
		cur = cur->character[index];
		if (!cur && cur->word->keyWord == keyword) {
			break;
		}
	}
	if (!cur) return;
	cur->isEdit = 0;
	delete cur->editedWord;
}

void resetEditWord(Trie tree, std::wstring path)
{
	std::wifstream fin(path);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	fin.imbue(loc);
	std::wstring get;
	getline(fin, get);
	while (!fin.eof())
	{
		std::vector<std::wstring> wordDef;
		std::wstring keyWord = get.substr(1, get.length() - 1);	//remove '@' character from key word
		removeEditWord(tree, keyWord);
		getline(fin, get);
		for (; !fin.eof() && get[0] != '@'; getline(fin, get))
		{

		}
	}
	fin.close();
}