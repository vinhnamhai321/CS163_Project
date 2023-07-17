#include "Dictionary.h"
#include <iostream>
int main()
{
	Trie ev;
	ev.loadDataSet(EV);
	std::wcout << "Search:";
	std::wstring inputString;
	getline(std::wcin, inputString);
	std::pair<Word,bool> ans = ev.search(inputString);
	if (!ans.second)
		std::wcout << "Can not find\n";
	else
	{
		std::wcout << "Word: " << ans.first.keyWord << std::endl;
		for (std::wstring item : ans.first.definition)
			std::wcout << item << std::endl;
	}
	ev.deleteTrie(ev.root);
	return 0;
}