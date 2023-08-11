#include "Trie.h"
#include <unordered_set>
#include<codecvt>
#include<locale>
#include<string>
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

void Trie::loadDataSet(std::string path, std::vector<WordDef> &word)
{	
	std::wifstream fin(path);
    std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
    fin.imbue(loc);
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
        WordDef w(keyWord, wordDef);
        word.push_back(w);

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
				break;
            case L'á':
                return 39;
                break;
            case L'à':
                return 40;
                break;
            case L'ả':
                return 41;
                break;
            case L'ã':
                return 42;
                break;
            case L'ạ':
                return 43;
                break;
            case L'é':
                return 44;
                break;
            case L'è':
                return 45;
                break;
            case L'ẻ':
                return 46;
                break;
            case L'ẽ':
                return 47;
                break;
            case L'ẹ':
                return 48;
                break;
            case L'ó':
                return 49;
                break;
            case L'ò':
                return 50;
                break;
            case L'ỏ':
                return 51;
                break;
            case L'õ':
                return 52;
                break;
            case L'ọ':
                return 53;
                break;
            case L'ú':
                return 54;
                break;
            case L'ù':
                return 55;
                break;
            case L'ủ':
                return 56;
                break;
            case L'ũ':
                return 57;
                break;
            case L'ụ':
                return 58;
                break;
            case L'ý':
                return 59;
                break;
            case L'ỳ':
                return 60;
                break;
            case L'ỷ':
                return 61;
                break;
            case L'ỹ':
                return 62;
                break;
            case L'ỵ':
                return 63;
                break;
            case L'ă':
                return 64;
                break;
            case L'ắ':
                return 65;
                break;
            case L'ằ':
                return 66;
                break;
            case L'ẳ':
                return 67;
                break;
            case L'ẵ':
                return 68;
                break;
            case L'ặ':
                return 69;
                break;
            case L'â':
                return 70;
                break;
            case L'ấ':
                return 71;
                break;
            case L'ầ':
                return 72;
                break;
            case L'ẩ':
                return 73;
                break;
            case L'ẫ':
                return 74;
                break;
            case L'ậ':
                return 75;
                break;
            case L'đ':
                return 76;
                break;
            case L'ê':
                return 77;
                break;
            case L'ế':
                return 78;
                break;
            case L'ề':
                return 79;
                break;
            case L'ể':
                return 80;
                break;
            case L'ễ':
                return 81;
                break;
            case L'ệ':
                return 82;
                break;
            case L'í':
                return 83;
                break;
            case L'ì':
                return 84;
                break;
            case L'ỉ':
                return 85;
                break;
            case L'ĩ':
                return 86;
                break;
            case L'ị':
                return 87;
                break;
            case L'ô':
                return 88;
                break;
            case L'ố':
                return 89;
                break;
            case L'ồ':
                return 90;
                break;
            case L'ổ':
                return 91;
                break;
            case L'ỗ':
                return 92;
                break;
            case L'ộ':
                return 93;
                break;
            case L'ơ':
                return 94;
                break;
            case L'ớ':
                return 95;
                break;
            case L'ờ':
                return 96;
                break;
            case L'ở':
                return 97;
                break;
            case L'ỡ':
                return 98;
                break;
            case L'ợ':
                return 99;
                break;
            case L'ư':
                return 100;
                break;
            case L'ứ':
                return 101;
                break;
            case L'ừ':
                return 102;
                break;
            case L'ử':
                return 103;
                break;
            case L'ữ':
                return 104;
                break;
            case L'ự':
                return 105;
                break;
			}
		}
	}
	return letter - L'a';
}

void Trie::deleteTrie(Node*& root)
{
	if (!root)
		return;
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

