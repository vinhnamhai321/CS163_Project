	#include "Dictionary.h"
	#include <iostream>
	int main()
	{
		Trie ev;
		ev.loadDataSet(EV);
		std::wcout << "Search:";
		std::wstring inputString;
		getline(std::wcin, inputString);
		WordDef* find = search(ev,inputString);
		if (!find)
			std::wcout << "Can not find this word in dictionary\n";
		else
		{
			std::wcout << "Word: " << find->keyWord << std::endl;
			for (std::wstring item : find->definition)
				std::wcout << item << std::endl;
		}
		ev.deleteTrie(ev.root);
		return 0;
	}